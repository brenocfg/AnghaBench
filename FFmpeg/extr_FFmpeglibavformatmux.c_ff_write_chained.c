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
struct TYPE_13__ {TYPE_1__** streams; } ;
struct TYPE_12__ {int stream_index; scalar_t__ pts; scalar_t__ dts; scalar_t__ duration; int /*<<< orphan*/  side_data_elems; int /*<<< orphan*/  side_data; int /*<<< orphan*/  buf; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int av_interleaved_write_frame (TYPE_3__*,TYPE_2__*) ; 
 void* av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_write_frame (TYPE_3__*,TYPE_2__*) ; 

int ff_write_chained(AVFormatContext *dst, int dst_stream, AVPacket *pkt,
                     AVFormatContext *src, int interleave)
{
    AVPacket local_pkt;
    int ret;

    local_pkt = *pkt;
    local_pkt.stream_index = dst_stream;
    if (pkt->pts != AV_NOPTS_VALUE)
        local_pkt.pts = av_rescale_q(pkt->pts,
                                     src->streams[pkt->stream_index]->time_base,
                                     dst->streams[dst_stream]->time_base);
    if (pkt->dts != AV_NOPTS_VALUE)
        local_pkt.dts = av_rescale_q(pkt->dts,
                                     src->streams[pkt->stream_index]->time_base,
                                     dst->streams[dst_stream]->time_base);
    if (pkt->duration)
        local_pkt.duration = av_rescale_q(pkt->duration,
                                          src->streams[pkt->stream_index]->time_base,
                                          dst->streams[dst_stream]->time_base);

    if (interleave) ret = av_interleaved_write_frame(dst, &local_pkt);
    else            ret = av_write_frame(dst, &local_pkt);
    pkt->buf = local_pkt.buf;
    pkt->side_data       = local_pkt.side_data;
    pkt->side_data_elems = local_pkt.side_data_elems;
    return ret;
}