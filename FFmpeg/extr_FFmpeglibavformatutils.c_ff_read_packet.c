#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int nb_streams; int flags; TYPE_2__* internal; scalar_t__ use_wallclock_as_timestamps; TYPE_3__** streams; TYPE_1__* iformat; } ;
struct TYPE_31__ {size_t stream_index; scalar_t__ size; int flags; void* pts; void* dts; int /*<<< orphan*/ * data; } ;
struct TYPE_30__ {struct TYPE_30__* next; TYPE_5__ pkt; } ;
struct TYPE_29__ {scalar_t__ request_probe; scalar_t__ pts_wrap_behavior; int /*<<< orphan*/  time_base; void* cur_dts; void* start_time; void* first_dts; scalar_t__ probe_packets; } ;
struct TYPE_28__ {scalar_t__ raw_packet_buffer_remaining_size; int /*<<< orphan*/  raw_packet_buffer_end; TYPE_4__* raw_packet_buffer; } ;
struct TYPE_27__ {int (* read_packet ) (TYPE_6__*,TYPE_5__*) ;} ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacketList ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_FLAG_DISCARD_CORRUPT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_PKT_FLAG_CORRUPT ; 
 scalar_t__ AV_PTS_WRAP_SUB_OFFSET ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  EAGAIN ; 
 int FFERROR_REDO ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (TYPE_4__*) ; 
 int /*<<< orphan*/  av_gettime () ; 
 int /*<<< orphan*/  av_init_packet (TYPE_5__*) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,size_t) ; 
 int av_packet_make_refcounted (TYPE_5__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 void* av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_packet_list_put (TYPE_4__**,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_codec_ids (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  is_relative (void*) ; 
 int probe_codec (TYPE_6__*,TYPE_3__*,TYPE_5__*) ; 
 int stub1 (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ update_wrap_reference (TYPE_6__*,TYPE_3__*,size_t,TYPE_5__*) ; 
 void* wrap_timestamp (TYPE_3__*,void*) ; 

int ff_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, i, err;
    AVStream *st;

    for (;;) {
        AVPacketList *pktl = s->internal->raw_packet_buffer;

        if (pktl) {
            *pkt = pktl->pkt;
            st   = s->streams[pkt->stream_index];
            if (s->internal->raw_packet_buffer_remaining_size <= 0)
                if ((err = probe_codec(s, st, NULL)) < 0)
                    return err;
            if (st->request_probe <= 0) {
                s->internal->raw_packet_buffer                 = pktl->next;
                s->internal->raw_packet_buffer_remaining_size += pkt->size;
                av_free(pktl);
                return 0;
            }
        }

        pkt->data = NULL;
        pkt->size = 0;
        av_init_packet(pkt);
        ret = s->iformat->read_packet(s, pkt);
        if (ret < 0) {
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
        if (err < 0)
            return err;

        if ((s->flags & AVFMT_FLAG_DISCARD_CORRUPT) &&
            (pkt->flags & AV_PKT_FLAG_CORRUPT)) {
            av_log(s, AV_LOG_WARNING,
                   "Dropped corrupted packet (stream = %d)\n",
                   pkt->stream_index);
            av_packet_unref(pkt);
            continue;
        }

        if (pkt->stream_index >= (unsigned)s->nb_streams) {
            av_log(s, AV_LOG_ERROR, "Invalid stream index %d\n", pkt->stream_index);
            continue;
        }

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
        if (err)
            return err;
        s->internal->raw_packet_buffer_remaining_size -= pkt->size;

        if ((err = probe_codec(s, st, pkt)) < 0)
            return err;
    }
}