#include "Common/config.h"
#include "Util/util.h"
#include "Util/onceToken.h"
#include "Network/sockutil.h"

#ifndef UINT64_MAX
#define UINT64_MAX 0xFFFFFFFFFFFFFFFF
#endif//UINT64_MAX

using namespace ZL::Network;

namespace Config {

void loaIniConfig(){
	auto &ini = ZL::Util::mINI::Instance();
	try{
		ini.parseFile(exePath() + ".ini");
	}catch (std::exception &ex) {
		ini.dumpFile(exePath() + ".ini");
	}
}
////////////广播名称///////////
namespace Broadcast {
const char kBroadcastRtspSessionPlay[] = "kBroadcastRtspSessionPlay";
const char kBroadcastRtspSrcRegisted[] = "kBroadcastRtspSrcRegisted";
const char kBroadcastRtmpSrcRegisted[] = "kBroadcastRtmpSrcRegisted";
const char kBroadcastRecordMP4[] = "kBroadcastRecordMP4";
const char kBroadcastHttpRequest[] = "kBroadcastHttpRequest";
} //namespace Broadcast

//代理失败最大重试次数
namespace Proxy {
#define PROXY_FIELD "proxy."

#define PROXY_REPLAY_CNT (UINT64_MAX)
const char kReplayCount[] = PROXY_FIELD"replayCount";

onceToken token([](){
	mINI::Instance()[kReplayCount] = PROXY_REPLAY_CNT;
},nullptr);

}//namespace Proxy


////////////HTTP配置///////////
namespace Http {
#define HTTP_FIELD "http."

#define HTTP_PORT 10080
const char kPort[] = HTTP_FIELD"port";

#define HTTPS_PORT 10443
extern const char kSSLPort[] = HTTP_FIELD"sslport";

//http 文件发送缓存大小
#define HTTP_SEND_BUF_SIZE (64 * 1024)
const char kSendBufSize[] = HTTP_FIELD"sendBufSize";

//http 最大请求字节数
#define HTTP_MAX_REQ_SIZE (4*1024)
const char kMaxReqSize[] = HTTP_FIELD"maxReqSize";

//http keep-alive秒数
#define HTTP_KEEP_ALIVE_SECOND 5
const char kKeepAliveSecond[] = HTTP_FIELD"keepAliveSecond";

//http keep-alive最大请求数
#define HTTP_MAX_REQ_CNT 100
const char kMaxReqCount[] = HTTP_FIELD"maxReqCount";

//http 字符编码
#define HTTP_CHAR_SET "utf-8"
const char kCharSet[] = HTTP_FIELD"charSet";

//http 服务器名称
#define HTTP_SERVER_NAME "ZLServer"
const char kServerName[] = HTTP_FIELD"serverName";

//http 服务器根目录
#define HTTP_ROOT_PATH (exeDir() + "httpRoot")
const char kRootPath[] = HTTP_FIELD"rootPath";

//http 404错误提示内容
#define HTTP_NOT_FOUND "<html>"\
		"<head><title>404 Not Found</title></head>"\
		"<body bgcolor=\"white\">"\
		"<center><h1>您访问的资源不存在！</h1></center>"\
		"<hr><center>"\
		 HTTP_SERVER_NAME\
		"</center>"\
		"</body>"\
		"</html>"
const char kNotFound[] = HTTP_FIELD"notFound";

//HTTP访问url前缀
#define HTTP_PREFIX (StrPrinter << "http://" \
						<< SockUtil::get_local_ip() \
						<< ":" << HTTP_PORT << endl)
const char kHttpPrefix[] = HTTP_FIELD"httpPrefix";

onceToken token([](){
	mINI::Instance()[kPort] = HTTP_PORT;
	mINI::Instance()[kSSLPort] = HTTPS_PORT;
	mINI::Instance()[kSendBufSize] = HTTP_SEND_BUF_SIZE;
	mINI::Instance()[kMaxReqSize] = HTTP_MAX_REQ_SIZE;
	mINI::Instance()[kKeepAliveSecond] = HTTP_KEEP_ALIVE_SECOND;
	mINI::Instance()[kMaxReqCount] = HTTP_MAX_REQ_CNT;
	mINI::Instance()[kCharSet] = HTTP_CHAR_SET;
	mINI::Instance()[kServerName] = HTTP_SERVER_NAME;
	mINI::Instance()[kRootPath] = HTTP_ROOT_PATH;
	mINI::Instance()[kNotFound] = HTTP_NOT_FOUND;
	mINI::Instance()[kHttpPrefix] = HTTP_PREFIX;
},nullptr);

}//namespace Http

////////////SHELL配置///////////
namespace Shell {
#define SHELL_FIELD "shell."

#define SHELL_PORT 19000
const char kPort[] = SHELL_FIELD"port";

#define SHELL_SERVER_NAME "ZLServer"
const char kServerName[] = SHELL_FIELD"serverName";

#define SHELL_MAX_REQ_SIZE 1024
const char kMaxReqSize[] = SHELL_FIELD"maxReqSize";

onceToken token([](){
	mINI::Instance()[kPort] = SHELL_PORT;
	mINI::Instance()[kServerName] = SHELL_SERVER_NAME;
	mINI::Instance()[kMaxReqSize] = SHELL_MAX_REQ_SIZE;
},nullptr);
} //namespace Shell

////////////RTSP服务器配置///////////
namespace Rtsp {
#define RTSP_FIELD "rtsp."

#define RTSP_PORT 10554
const char kPort[] = RTSP_FIELD"port";

#define RTSP_SERVER_NAME "ZLServer"
const char kServerName[] = RTSP_FIELD"serverName";

onceToken token([](){
	mINI::Instance()[kPort] = RTSP_PORT;
	mINI::Instance()[kServerName] = RTSP_SERVER_NAME;
},nullptr);

} //namespace Rtsp

////////////RTMP服务器配置///////////
namespace Rtmp {
#define RTMP_FIELD "rtmp."

#define RTMP_PORT 11935
const char kPort[] = RTMP_FIELD"port";

onceToken token([](){
	mINI::Instance()[kPort] = RTMP_PORT;
},nullptr);
} //namespace RTMP


////////////RTP配置///////////
namespace Rtp {
#define RTP_FIELD "rtp."

//RTP打包最大MTU,公网情况下更小
#define RTP_VIDOE_MTU_SIZE 1400
const char kVideoMtuSize[] = RTP_FIELD"videoMtuSize";

#define RTP_Audio_MTU_SIZE 600
const char kAudioMtuSize[] = RTP_FIELD"audioMtuSize";

//udp方式接受RTP包的最大缓存
#define RTP_UDP_BUFSIZE (128 * 1024)
const char kUdpBufSize[] = RTP_FIELD"udpBufSize";

//RTP排序缓存最大个数
#define RTP_MAX_RTP_COUNT 50
const char kMaxRtpCount[] = RTP_FIELD"maxRtpCount";

//如果RTP序列正确次数累计达到该数字就启动清空排序缓存
#define RTP_CLEAR_COUNT 10
const char kClearCount[] = RTP_FIELD"clearCount";

//最大RTP时间为13个小时，每13小时回环一次
#define RTP_CYCLE_MS (13*60*60*1000)
const char kCycleMS[] = RTP_FIELD"cycleMS";


onceToken token([](){
	mINI::Instance()[kVideoMtuSize] = RTP_VIDOE_MTU_SIZE;
	mINI::Instance()[kAudioMtuSize] = RTP_Audio_MTU_SIZE;
	mINI::Instance()[kUdpBufSize] = RTP_UDP_BUFSIZE;
	mINI::Instance()[kMaxRtpCount] = RTP_MAX_RTP_COUNT;
	mINI::Instance()[kClearCount] = RTP_CLEAR_COUNT;
	mINI::Instance()[kCycleMS] = RTP_CYCLE_MS;
},nullptr);
} //namespace Rtsp

////////////组播配置///////////
namespace MultiCast {
#define MULTI_FIELD "multicast."
//组播分配起始地址
#define MULTI_ADDR_MIN (0xE00000FF + 10)
const char kAddrMin[] = MULTI_FIELD"addrMin";

//组播分配截止地址
#define MULTI_ADDR_MAX (0xEFFFFFFF)
const char kAddrMax[] = MULTI_FIELD"addrMax";

//组播TTL
#define MULTI_UDP_TTL 64
const char kUdpTTL[] = MULTI_FIELD"udpTTL";

onceToken token([](){
	mINI::Instance()[kAddrMin] = MULTI_ADDR_MIN;
	mINI::Instance()[kAddrMax] = MULTI_ADDR_MAX;
	mINI::Instance()[kUdpTTL] = MULTI_UDP_TTL;
},nullptr);

} //namespace MultiCast

////////////录像配置///////////
namespace Record {
#define RECORD_FIELD "record."

//查看录像的应用名称
#define RECORD_APP_NAME "record"
const char kAppName[] = RECORD_FIELD"appName";

//每次流化MP4文件的时长,单位毫秒
#define RECORD_SAMPLE_MS 100
const char kSampleMS[] = RECORD_FIELD"sampleMS";

//MP4文件录制大小,不能太大,否则MP4Close函数执行事件太长
#define RECORD_FILE_SECOND (10*60)
const char kFileSecond[] = RECORD_FIELD"fileSecond";

//Rtsp访问url前缀
#define RECORD_RTSP_PREFIX (StrPrinter << "rtsp://" \
							<< SockUtil::get_local_ip() \
							<< ":" << RTSP_PORT << endl)
const char kRtspPrefix[] = RECORD_FIELD"rtspPrefix";

//录制文件路径
#define RECORD_FILE_PATH HTTP_ROOT_PATH
const char kFilePath[] = RECORD_FIELD"filePath";

onceToken token([](){
	mINI::Instance()[kAppName] = RECORD_APP_NAME;
	mINI::Instance()[kSampleMS] = RECORD_SAMPLE_MS;
	mINI::Instance()[kFileSecond] = RECORD_FILE_SECOND;
	mINI::Instance()[kFilePath] = RECORD_FILE_PATH;
	mINI::Instance()[kRtspPrefix] = RECORD_RTSP_PREFIX;
},nullptr);

} //namespace Record

////////////HLS相关配置///////////
namespace Hls {
#define HLS_FIELD "hls."

//HLS切片时长,单位秒
#define HLS_SEGMENT_DURATION 5
const char kSegmentDuration[] = HLS_FIELD"segDur";

//HLS切片个数
#define HLS_SEGMENT_NUM 3
const char kSegmentNum[] = HLS_FIELD"segNum";

//HLS文件写缓存大小
#define HLS_FILE_BUF_SIZE (64 * 1024)
const char kFileBufSize[] = HLS_FIELD"fileBufSize";

//录制文件路径
#define HLS_FILE_PATH (HTTP_ROOT_PATH)
const char kFilePath[] = HLS_FIELD"filePath";

onceToken token([](){
	mINI::Instance()[kSegmentDuration] = HLS_SEGMENT_DURATION;
	mINI::Instance()[kSegmentNum] = HLS_SEGMENT_NUM;
	mINI::Instance()[kFileBufSize] = HLS_FILE_BUF_SIZE;
	mINI::Instance()[kFilePath] = HLS_FILE_PATH;
},nullptr);

} //namespace Hls

}  // namespace Config


