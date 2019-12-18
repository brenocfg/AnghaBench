#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv_data; } ;
struct TYPE_8__ {scalar_t__ status_code; } ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ server_type; int /*<<< orphan*/  control_uri; scalar_t__ need_subscription; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ RTSPMessageHeader ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ RTSP_SERVER_REAL ; 
 scalar_t__ RTSP_STATE_PAUSED ; 
 scalar_t__ RTSP_STATE_STREAMING ; 
 scalar_t__ RTSP_STATUS_OK ; 
 int ff_rtsp_averror (scalar_t__,int) ; 
 int /*<<< orphan*/  ff_rtsp_send_cmd (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtsp_read_pause(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    RTSPMessageHeader reply1, *reply = &reply1;

    if (rt->state != RTSP_STATE_STREAMING)
        return 0;
    else if (!(rt->server_type == RTSP_SERVER_REAL && rt->need_subscription)) {
        ff_rtsp_send_cmd(s, "PAUSE", rt->control_uri, NULL, reply, NULL);
        if (reply->status_code != RTSP_STATUS_OK) {
            return ff_rtsp_averror(reply->status_code, -1);
        }
    }
    rt->state = RTSP_STATE_PAUSED;
    return 0;
}