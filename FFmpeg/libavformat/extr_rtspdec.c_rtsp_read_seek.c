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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {TYPE_1__** streams; TYPE_2__* priv_data; } ;
struct TYPE_8__ {int state; int /*<<< orphan*/  seek_timestamp; } ;
struct TYPE_7__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ RTSPState ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
#define  RTSP_STATE_IDLE 130 
#define  RTSP_STATE_PAUSED 129 
 int RTSP_STATE_SEEKING ; 
#define  RTSP_STATE_STREAMING 128 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtsp_read_pause (TYPE_3__*) ; 
 int rtsp_read_play (TYPE_3__*) ; 

__attribute__((used)) static int rtsp_read_seek(AVFormatContext *s, int stream_index,
                          int64_t timestamp, int flags)
{
    RTSPState *rt = s->priv_data;
    int ret;

    rt->seek_timestamp = av_rescale_q(timestamp,
                                      s->streams[stream_index]->time_base,
                                      AV_TIME_BASE_Q);
    switch(rt->state) {
    default:
    case RTSP_STATE_IDLE:
        break;
    case RTSP_STATE_STREAMING:
        if ((ret = rtsp_read_pause(s)) != 0)
            return ret;
        rt->state = RTSP_STATE_SEEKING;
        if ((ret = rtsp_read_play(s)) != 0)
            return ret;
        break;
    case RTSP_STATE_PAUSED:
        rt->state = RTSP_STATE_IDLE;
        break;
    }
    return 0;
}