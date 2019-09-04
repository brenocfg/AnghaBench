#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ time_frame; int /*<<< orphan*/  time_base; } ;
typedef  TYPE_1__ XCBGrabContext ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ pts; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ av_gettime () ; 
 scalar_t__ av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_usleep (scalar_t__) ; 

__attribute__((used)) static void wait_frame(AVFormatContext *s, AVPacket *pkt)
{
    XCBGrabContext *c = s->priv_data;
    int64_t curtime, delay;
    int64_t frame_time = av_rescale_q(1, c->time_base, AV_TIME_BASE_Q);

    c->time_frame += frame_time;

    for (;;) {
        curtime = av_gettime();
        delay   = c->time_frame - curtime;
        if (delay <= 0)
            break;
        av_usleep(delay);
    }

    pkt->pts = curtime;
}