#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_22__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_38__ {int nb_streams; int flags; TYPE_3__* internal; scalar_t__ use_wallclock_as_timestamps; TYPE_4__** streams; TYPE_2__* iformat; } ;
struct TYPE_37__ {scalar_t__ size; int flags; unsigned int stream_index; void* pts; void* dts; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {size_t stream_index; } ;
struct TYPE_36__ {TYPE_1__ pkt; } ;
struct TYPE_35__ {scalar_t__ request_probe; scalar_t__ pts_wrap_behavior; int /*<<< orphan*/  time_base; void* cur_dts; void* start_time; void* first_dts; scalar_t__ probe_packets; } ;
struct TYPE_34__ {scalar_t__ raw_packet_buffer_remaining_size; TYPE_22__* raw_packet_buffer_end; TYPE_5__* raw_packet_buffer; } ;
struct TYPE_33__ {int (* read_packet ) (TYPE_7__*,TYPE_6__*) ;} ;
struct TYPE_32__ {TYPE_6__ pkt; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacketList ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_FLAG_DISCARD_CORRUPT ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_PKT_FLAG_CORRUPT ; 
 scalar_t__ AV_PTS_WRAP_SUB_OFFSET ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  EAGAIN ; 
 int FFERROR_REDO ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_gettime () ; 
 int /*<<< orphan*/  av_init_packet (TYPE_6__*) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int av_packet_make_refcounted (TYPE_6__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_6__*) ; 
 void* av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_packet_list_get (TYPE_5__**,TYPE_22__**,TYPE_6__*) ; 
 int ff_packet_list_put (TYPE_5__**,TYPE_22__**,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_codec_ids (TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  is_relative (void*) ; 
 int probe_codec (TYPE_7__*,TYPE_4__*,TYPE_6__ const*) ; 
 int stub1 (TYPE_7__*,TYPE_6__*) ; 
 scalar_t__ update_wrap_reference (TYPE_7__*,TYPE_4__*,size_t,TYPE_6__*) ; 
 void* wrap_timestamp (TYPE_4__*,void*) ; 

int ff_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, i, err;
    AVStream *st;

    pkt->data = NULL;
    pkt->size = 0;
    av_init_packet(pkt);

    for (;;) {
        AVPacketList *pktl = s->internal->raw_packet_buffer;
        const AVPacket *pkt1;

        if (pktl) {
            st = s->streams[pktl->pkt.stream_index];
            if (s->internal->raw_packet_buffer_remaining_size <= 0)
                if ((err = probe_codec(s, st, NULL)) < 0)
                    return err;
            if (st->request_probe <= 0) {
                ff_packet_list_get(&s->internal->raw_packet_buffer,
                                   &s->internal->raw_packet_buffer_end, pkt);
                s->internal->raw_packet_buffer_remaining_size += pkt->size;
                return 0;
            }
        }

        ret = s->iformat->read_packet(s, pkt);
        if (ret < 0) {
            av_packet_unref(pkt);

            /* Some demuxers return FFERROR_REDO when they consume
               data and discard it (ignored streams, junk, extradata).
               We must re-call the demuxer to get the real packet. */
            if (ret == FFERROR_REDO)
                continue;
            if (!pktl || ret == AVERROR(EAGAIN))
                return ret;
            for (i = 0; i < s->nb_streams; i++) {
                st = s->streams[i];
                if (st->probe_packets || st->request_probe > 0)
                    if ((err = probe_codec(s, st, NULL)) < 0)
                        return err;
                av_assert0(st->request_probe <= 0);
            }
            continue;
        }

        err = av_packet_make_refcounted(pkt);
        if (err < 0) {
            av_packet_unref(pkt);
            return err;
        }

        if ((s->flags & AVFMT_FLAG_DISCARD_CORRUPT) &&
            (pkt->flags & AV_PKT_FLAG_CORRUPT)) {
            av_log(s, AV_LOG_WARNING,
                   "Dropped corrupted packet (stream = %d)\n",
                   pkt->stream_index);
            av_packet_unref(pkt);
            continue;
        }

        av_assert0(pkt->stream_index < (unsigned)s->nb_streams &&
                   "Invalid stream index.\n");

        st = s->streams[pkt->stream_index];

        if (update_wrap_reference(s, st, pkt->stream_index, pkt) && st->pts_wrap_behavior == AV_PTS_WRAP_SUB_OFFSET) {
            // correct first time stamps to negative values
            if (!is_relative(st->first_dts))
                st->first_dts = wrap_timestamp(st, st->first_dts);
            if (!is_relative(st->start_time))
                st->start_time = wrap_timestamp(st, st->start_time);
            if (!is_relative(st->cur_dts))
                st->cur_dts = wrap_timestamp(st, st->cur_dts);
        }

        pkt->dts = wrap_timestamp(st, pkt->dts);
        pkt->pts = wrap_timestamp(st, pkt->pts);

        force_codec_ids(s, st);

        /* TODO: audio: time filter; video: frame reordering (pts != dts) */
        if (s->use_wallclock_as_timestamps)
            pkt->dts = pkt->pts = av_rescale_q(av_gettime(), AV_TIME_BASE_Q, st->time_base);

        if (!pktl && st->request_probe <= 0)
            return ret;

        err = ff_packet_list_put(&s->internal->raw_packet_buffer,
                                 &s->internal->raw_packet_buffer_end,
                                 pkt, 0);
        if (err < 0) {
            av_packet_unref(pkt);
            return err;
        }
        pkt1 = &s->internal->raw_packet_buffer_end->pkt;
        s->internal->raw_packet_buffer_remaining_size -= pkt1->size;

        if ((err = probe_codec(s, st, pkt1)) < 0)
            return err;
    }
}