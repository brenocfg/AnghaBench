#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_12__ {scalar_t__ output_ts_offset; TYPE_2__** streams; TYPE_1__* internal; } ;
struct TYPE_11__ {int stream_index; scalar_t__ dts; scalar_t__ pts; } ;
struct TYPE_10__ {struct TYPE_10__* next; TYPE_4__ pkt; } ;
struct TYPE_9__ {scalar_t__ mux_ts_offset; int /*<<< orphan*/  time_base; } ;
struct TYPE_8__ {TYPE_3__* packet_buffer; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacketList ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_interleaved_peek(AVFormatContext *s, int stream,
                        AVPacket *pkt, int add_offset)
{
    AVPacketList *pktl = s->internal->packet_buffer;
    while (pktl) {
        if (pktl->pkt.stream_index == stream) {
            *pkt = pktl->pkt;
            if (add_offset) {
                AVStream *st = s->streams[pkt->stream_index];
                int64_t offset = st->mux_ts_offset;

                if (s->output_ts_offset)
                    offset += av_rescale_q(s->output_ts_offset, AV_TIME_BASE_Q, st->time_base);

                if (pkt->dts != AV_NOPTS_VALUE)
                    pkt->dts += offset;
                if (pkt->pts != AV_NOPTS_VALUE)
                    pkt->pts += offset;
            }
            return 0;
        }
        pktl = pktl->next;
    }
    return AVERROR(ENOENT);
}