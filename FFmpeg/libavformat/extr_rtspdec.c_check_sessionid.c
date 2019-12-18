#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  session_id; } ;
struct TYPE_8__ {unsigned char* session_id; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ RTSPMessageHeader ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_STREAM_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  RTSP_STATUS_SESSION ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtsp_send_reply (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check_sessionid(AVFormatContext *s,
                                  RTSPMessageHeader *request)
{
    RTSPState *rt = s->priv_data;
    unsigned char *session_id = rt->session_id;
    if (!session_id[0]) {
        av_log(s, AV_LOG_WARNING, "There is no session-id at the moment\n");
        return 0;
    }
    if (strcmp(session_id, request->session_id)) {
        av_log(s, AV_LOG_ERROR, "Unexpected session-id %s\n",
               request->session_id);
        rtsp_send_reply(s, RTSP_STATUS_SESSION, NULL, request->seq);
        return AVERROR_STREAM_NOT_FOUND;
    }
    return 0;
}