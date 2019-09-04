#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int int64_t ;
struct TYPE_27__ {int buf; } ;
struct TYPE_24__ {size_t stream_index; int flags; scalar_t__ size; int duration; int dts; scalar_t__ side_data_elems; int /*<<< orphan*/ * side_data; int /*<<< orphan*/ * buf; scalar_t__ data; } ;
struct TYPE_26__ {struct TYPE_26__* next; TYPE_4__ pkt; } ;
struct TYPE_25__ {scalar_t__ interleaver_chunk_size; int interleaver_chunk_duration; TYPE_7__* last_in_packet_buffer; TYPE_1__* codecpar; int /*<<< orphan*/  time_base; } ;
struct TYPE_23__ {scalar_t__ max_chunk_size; TYPE_6__** streams; TYPE_2__* internal; scalar_t__ max_chunk_duration; } ;
struct TYPE_22__ {TYPE_7__* packet_buffer_end; TYPE_7__* packet_buffer; } ;
struct TYPE_21__ {scalar_t__ codec_type; } ;
typedef  TYPE_6__ AVStream ;
typedef  TYPE_7__ AVPacketList ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_9__ AVFrame ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int AV_PKT_FLAG_UNCODED_FRAME ; 
 int /*<<< orphan*/  AV_ROUND_UP ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int CHUNK_START ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ UNCODED_FRAME_PACKET_SIZE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_free (TYPE_7__*) ; 
 TYPE_7__* av_mallocz (int) ; 
 int av_packet_ref (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int av_rescale (int,int,int) ; 
 int av_rescale_q_rnd (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_interleave_add_packet(AVFormatContext *s, AVPacket *pkt,
                             int (*compare)(AVFormatContext *, AVPacket *, AVPacket *))
{
    int ret;
    AVPacketList **next_point, *this_pktl;
    AVStream *st   = s->streams[pkt->stream_index];
    int chunked    = s->max_chunk_size || s->max_chunk_duration;

    this_pktl      = av_mallocz(sizeof(AVPacketList));
    if (!this_pktl)
        return AVERROR(ENOMEM);
    if ((pkt->flags & AV_PKT_FLAG_UNCODED_FRAME)) {
        av_assert0(pkt->size == UNCODED_FRAME_PACKET_SIZE);
        av_assert0(((AVFrame *)pkt->data)->buf);
        this_pktl->pkt = *pkt;
        pkt->buf = NULL;
        pkt->side_data = NULL;
        pkt->side_data_elems = 0;
    } else {
        if ((ret = av_packet_ref(&this_pktl->pkt, pkt)) < 0) {
            av_free(this_pktl);
            return ret;
        }
    }

    if (s->streams[pkt->stream_index]->last_in_packet_buffer) {
        next_point = &(st->last_in_packet_buffer->next);
    } else {
        next_point = &s->internal->packet_buffer;
    }

    if (chunked) {
        uint64_t max= av_rescale_q_rnd(s->max_chunk_duration, AV_TIME_BASE_Q, st->time_base, AV_ROUND_UP);
        st->interleaver_chunk_size     += pkt->size;
        st->interleaver_chunk_duration += pkt->duration;
        if (   (s->max_chunk_size && st->interleaver_chunk_size > s->max_chunk_size)
            || (max && st->interleaver_chunk_duration           > max)) {
            st->interleaver_chunk_size      = 0;
            this_pktl->pkt.flags |= CHUNK_START;
            if (max && st->interleaver_chunk_duration > max) {
                int64_t syncoffset = (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)*max/2;
                int64_t syncto = av_rescale(pkt->dts + syncoffset, 1, max)*max - syncoffset;

                st->interleaver_chunk_duration += (pkt->dts - syncto)/8 - max;
            } else
                st->interleaver_chunk_duration = 0;
        }
    }
    if (*next_point) {
        if (chunked && !(this_pktl->pkt.flags & CHUNK_START))
            goto next_non_null;

        if (compare(s, &s->internal->packet_buffer_end->pkt, pkt)) {
            while (   *next_point
                   && ((chunked && !((*next_point)->pkt.flags&CHUNK_START))
                       || !compare(s, &(*next_point)->pkt, pkt)))
                next_point = &(*next_point)->next;
            if (*next_point)
                goto next_non_null;
        } else {
            next_point = &(s->internal->packet_buffer_end->next);
        }
    }
    av_assert1(!*next_point);

    s->internal->packet_buffer_end = this_pktl;
next_non_null:

    this_pktl->next = *next_point;

    s->streams[pkt->stream_index]->last_in_packet_buffer =
        *next_point                                      = this_pktl;

    av_packet_unref(pkt);

    return 0;
}