#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int stream_index; scalar_t__ pts; scalar_t__ dts; int /*<<< orphan*/ * data; scalar_t__ size; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 scalar_t__ audio_dts ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  av_write_frame (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ctx ; 
 scalar_t__ video_dts ; 

__attribute__((used)) static void signal_init_ts(void)
{
    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.size = 0;
    pkt.data = NULL;

    pkt.stream_index = 0;
    pkt.dts = video_dts;
    pkt.pts = 0;
    av_write_frame(ctx, &pkt);

    pkt.stream_index = 1;
    pkt.dts = pkt.pts = audio_dts;
    av_write_frame(ctx, &pkt);
}