#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uri ;
typedef  int /*<<< orphan*/  rbuf ;
typedef  int /*<<< orphan*/  method ;
typedef  enum RTSPMethod { ____Placeholder_RTSPMethod } RTSPMethod ;
struct TYPE_13__ {TYPE_1__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  state; int /*<<< orphan*/  seq; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ RTSPMessageHeader ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int OPTIONS ; 
 int PAUSE ; 
 int /*<<< orphan*/  RTSP_STATE_IDLE ; 
 int /*<<< orphan*/  RTSP_STATE_PAUSED ; 
 int /*<<< orphan*/  RTSP_STATUS_OK ; 
 int TEARDOWN ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int parse_command_line (TYPE_3__*,unsigned char*,int,char*,int,unsigned char*,int,int*) ; 
 int read_line (TYPE_3__*,unsigned char*,int,int*) ; 
 int rtsp_read_request (TYPE_3__*,TYPE_2__*,unsigned char*) ; 
 int rtsp_send_reply (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int ff_rtsp_parse_streaming_commands(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    unsigned char rbuf[4096];
    unsigned char method[10];
    char uri[500];
    int ret;
    int rbuflen               = 0;
    RTSPMessageHeader request = { 0 };
    enum RTSPMethod methodcode;

    ret = read_line(s, rbuf, sizeof(rbuf), &rbuflen);
    if (ret < 0)
        return ret;
    ret = parse_command_line(s, rbuf, rbuflen, uri, sizeof(uri), method,
                             sizeof(method), &methodcode);
    if (ret) {
        av_log(s, AV_LOG_ERROR, "RTSP: Unexpected Command\n");
        return ret;
    }

    ret = rtsp_read_request(s, &request, method);
    if (ret)
        return ret;
    rt->seq++;
    if (methodcode == PAUSE) {
        rt->state = RTSP_STATE_PAUSED;
        ret       = rtsp_send_reply(s, RTSP_STATUS_OK, NULL , request.seq);
        // TODO: Missing date header in response
    } else if (methodcode == OPTIONS) {
        ret = rtsp_send_reply(s, RTSP_STATUS_OK,
                              "Public: ANNOUNCE, PAUSE, SETUP, TEARDOWN, "
                              "RECORD\r\n", request.seq);
    } else if (methodcode == TEARDOWN) {
        rt->state = RTSP_STATE_IDLE;
        ret       = rtsp_send_reply(s, RTSP_STATUS_OK, NULL , request.seq);
    }
    return ret;
}