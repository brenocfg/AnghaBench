#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_12__ {TYPE_1__* priv_data; } ;
struct TYPE_11__ {scalar_t__ status_code; } ;
struct TYPE_10__ {scalar_t__ server_type; int /*<<< orphan*/  control_uri; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ RTSPMessageHeader ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ RTSP_SERVER_REAL ; 
 scalar_t__ RTSP_STATUS_OK ; 
 int /*<<< orphan*/  av_freep (unsigned char**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,unsigned char*) ; 
 int /*<<< orphan*/  av_strlcat (char*,char*,int) ; 
 int ff_rtsp_averror (scalar_t__,int) ; 
 int /*<<< orphan*/  ff_rtsp_send_cmd (TYPE_3__*,char*,int /*<<< orphan*/ ,char*,TYPE_2__*,unsigned char**) ; 
 int ff_sdp_parse (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 

int ff_rtsp_setup_input_streams(AVFormatContext *s, RTSPMessageHeader *reply)
{
    RTSPState *rt = s->priv_data;
    char cmd[1024];
    unsigned char *content = NULL;
    int ret;

    /* describe the stream */
    snprintf(cmd, sizeof(cmd),
             "Accept: application/sdp\r\n");
    if (rt->server_type == RTSP_SERVER_REAL) {
        /**
         * The Require: attribute is needed for proper streaming from
         * Realmedia servers.
         */
        av_strlcat(cmd,
                   "Require: com.real.retain-entity-for-setup\r\n",
                   sizeof(cmd));
    }
    ff_rtsp_send_cmd(s, "DESCRIBE", rt->control_uri, cmd, reply, &content);
    if (reply->status_code != RTSP_STATUS_OK) {
        av_freep(&content);
        return ff_rtsp_averror(reply->status_code, AVERROR_INVALIDDATA);
    }
    if (!content)
        return AVERROR_INVALIDDATA;

    av_log(s, AV_LOG_VERBOSE, "SDP:\n%s\n", content);
    /* now we got the SDP description, we parse it */
    ret = ff_sdp_parse(s, (const char *)content);
    av_freep(&content);
    if (ret < 0)
        return ret;

    return 0;
}