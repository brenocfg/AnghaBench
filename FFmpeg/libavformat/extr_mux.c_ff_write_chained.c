#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__** streams; } ;
struct TYPE_13__ {int stream_index; int /*<<< orphan*/  side_data_elems; int /*<<< orphan*/  side_data; int /*<<< orphan*/  buf; } ;
struct TYPE_12__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int av_interleaved_write_frame (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_rescale_ts (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_write_frame (TYPE_3__*,TYPE_2__*) ; 

int ff_write_chained(AVFormatContext *dst, int dst_stream, AVPacket *pkt,
                     AVFormatContext *src, int interleave)
{
    AVPacket local_pkt;
    int ret;

    local_pkt = *pkt;
    local_pkt.stream_index = dst_stream;

    av_packet_rescale_ts(&local_pkt,
                         src->streams[pkt->stream_index]->time_base,
                         dst->streams[dst_stream]->time_base);

    if (interleave) ret = av_interleaved_write_frame(dst, &local_pkt);
    else            ret = av_write_frame(dst, &local_pkt);
    pkt->buf = local_pkt.buf;
    pkt->side_data       = local_pkt.side_data;
    pkt->side_data_elems = local_pkt.side_data_elems;
    return ret;
}