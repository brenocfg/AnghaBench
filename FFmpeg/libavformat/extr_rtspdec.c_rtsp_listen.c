#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uri ;
typedef  int /*<<< orphan*/  tcpname ;
typedef  int /*<<< orphan*/  rbuf ;
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  method ;
typedef  int /*<<< orphan*/  host ;
typedef  enum RTSPMethod { ____Placeholder_RTSPMethod } RTSPMethod ;
typedef  int /*<<< orphan*/  auth ;
struct TYPE_12__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  url; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int initial_timeout; int /*<<< orphan*/  rtsp_hd; int /*<<< orphan*/  state; int /*<<< orphan*/  rtsp_hd_out; int /*<<< orphan*/  control_uri; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int ANNOUNCE ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int OPTIONS ; 
 int RECORD ; 
 int RTSPS_DEFAULT_PORT ; 
 int RTSP_DEFAULT_PORT ; 
 int /*<<< orphan*/  RTSP_STATE_IDLE ; 
 int /*<<< orphan*/  RTSP_STATE_PAUSED ; 
 int SETUP ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_url_split (char*,int,char*,int,char*,int,int*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char const*,int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int /*<<< orphan*/  ffurl_close (int /*<<< orphan*/ ) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_command_line (TYPE_2__*,unsigned char*,int,char*,int,unsigned char*,int,int*) ; 
 int read_line (TYPE_2__*,unsigned char*,int,int*) ; 
 int rtsp_read_announce (TYPE_2__*) ; 
 int rtsp_read_options (TYPE_2__*) ; 
 int rtsp_read_record (TYPE_2__*) ; 
 int rtsp_read_setup (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int rtsp_listen(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    char proto[128], host[128], path[512], auth[128];
    char uri[500];
    int port;
    int default_port = RTSP_DEFAULT_PORT;
    char tcpname[500];
    const char *lower_proto = "tcp";
    unsigned char rbuf[4096];
    unsigned char method[10];
    int rbuflen = 0;
    int ret;
    enum RTSPMethod methodcode;

    /* extract hostname and port */
    av_url_split(proto, sizeof(proto), auth, sizeof(auth), host, sizeof(host),
                 &port, path, sizeof(path), s->url);

    /* ff_url_join. No authorization by now (NULL) */
    ff_url_join(rt->control_uri, sizeof(rt->control_uri), proto, NULL, host,
                port, "%s", path);

    if (!strcmp(proto, "rtsps")) {
        lower_proto  = "tls";
        default_port = RTSPS_DEFAULT_PORT;
    }

    if (port < 0)
        port = default_port;

    /* Create TCP connection */
    ff_url_join(tcpname, sizeof(tcpname), lower_proto, NULL, host, port,
                "?listen&listen_timeout=%d", rt->initial_timeout * 1000);

    if (ret = ffurl_open_whitelist(&rt->rtsp_hd, tcpname, AVIO_FLAG_READ_WRITE,
                                   &s->interrupt_callback, NULL,
                                   s->protocol_whitelist, s->protocol_blacklist, NULL)) {
        av_log(s, AV_LOG_ERROR, "Unable to open RTSP for listening\n");
        return ret;
    }
    rt->state       = RTSP_STATE_IDLE;
    rt->rtsp_hd_out = rt->rtsp_hd;
    for (;;) { /* Wait for incoming RTSP messages */
        ret = read_line(s, rbuf, sizeof(rbuf), &rbuflen);
        if (ret < 0)
            return ret;
        ret = parse_command_line(s, rbuf, rbuflen, uri, sizeof(uri), method,
                                 sizeof(method), &methodcode);
        if (ret) {
            av_log(s, AV_LOG_ERROR, "RTSP: Unexpected Command\n");
            return ret;
        }

        if (methodcode == ANNOUNCE) {
            ret       = rtsp_read_announce(s);
            rt->state = RTSP_STATE_PAUSED;
        } else if (methodcode == OPTIONS) {
            ret = rtsp_read_options(s);
        } else if (methodcode == RECORD) {
            ret = rtsp_read_record(s);
            if (!ret)
                return 0; // We are ready for streaming
        } else if (methodcode == SETUP)
            ret = rtsp_read_setup(s, host, uri);
        if (ret) {
            ffurl_close(rt->rtsp_hd);
            return AVERROR_INVALIDDATA;
        }
    }
}