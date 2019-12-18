#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  stream_index; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; int /*<<< orphan*/  time_base; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int av_interleaved_write_frame (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_rescale_ts (TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_packet (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int write_frame(AVFormatContext *fmt_ctx, const AVRational *time_base, AVStream *st, AVPacket *pkt)
{
    /* rescale output packet timestamp values from codec to stream timebase */
    av_packet_rescale_ts(pkt, *time_base, st->time_base);
    pkt->stream_index = st->index;

    /* Write the compressed frame to the media file. */
    log_packet(fmt_ctx, pkt);
    return av_interleaved_write_frame(fmt_ctx, pkt);
}