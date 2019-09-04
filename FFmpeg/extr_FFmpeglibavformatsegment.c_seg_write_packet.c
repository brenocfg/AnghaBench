#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int time_t ;
struct tm {int tm_hour; int tm_min; scalar_t__ tm_sec; } ;
typedef  int int64_t ;
struct TYPE_20__ {TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_19__ {size_t stream_index; scalar_t__ pts; scalar_t__ duration; int flags; scalar_t__ dts; } ;
struct TYPE_18__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_16__ {scalar_t__ last_duration; double end_time; double start_time; scalar_t__ start_pts; scalar_t__ index; } ;
struct TYPE_17__ {int* times; size_t segment_count; size_t nb_times; int* frames; size_t nb_frames; int clocktime_offset; int time; int last_val; int clocktime_wrap_duration; int cut_pending; scalar_t__ reference_stream_index; int frame_count; scalar_t__ segment_frame_count; int segment_idx_wrap; int segment_idx_wrap_nb; scalar_t__ initial_offset; scalar_t__ reset_timestamps; TYPE_10__* avf; TYPE_1__ cur_entry; scalar_t__ write_empty; scalar_t__ use_clocktime; scalar_t__ segment_idx; int /*<<< orphan*/  individual_header_trailer; scalar_t__ time_delta; scalar_t__ break_non_keyframes; } ;
struct TYPE_15__ {int /*<<< orphan*/  url; int /*<<< orphan*/  pb; } ;
typedef  TYPE_2__ SegmentContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  EINVAL ; 
 double FFMAX (double,double) ; 
 int INT64_MAX ; 
 int INT_MAX ; 
 scalar_t__ av_compare_ts (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 void* av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_ts2str (scalar_t__) ; 
 int /*<<< orphan*/  av_ts2timestr (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_5__*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ff_write_chained (TYPE_10__*,scalar_t__,TYPE_4__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  localtime_r (int*,struct tm*) ; 
 int segment_end (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int segment_start (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seg_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    SegmentContext *seg = s->priv_data;
    AVStream *st = s->streams[pkt->stream_index];
    int64_t end_pts = INT64_MAX, offset;
    int start_frame = INT_MAX;
    int ret;
    struct tm ti;
    int64_t usecs;
    int64_t wrapped_val;

    if (!seg->avf || !seg->avf->pb)
        return AVERROR(EINVAL);

calc_times:
    if (seg->times) {
        end_pts = seg->segment_count < seg->nb_times ?
            seg->times[seg->segment_count] : INT64_MAX;
    } else if (seg->frames) {
        start_frame = seg->segment_count < seg->nb_frames ?
            seg->frames[seg->segment_count] : INT_MAX;
    } else {
        if (seg->use_clocktime) {
            int64_t avgt = av_gettime();
            time_t sec = avgt / 1000000;
            localtime_r(&sec, &ti);
            usecs = (int64_t)(ti.tm_hour * 3600 + ti.tm_min * 60 + ti.tm_sec) * 1000000 + (avgt % 1000000);
            wrapped_val = (usecs + seg->clocktime_offset) % seg->time;
            if (wrapped_val < seg->last_val && wrapped_val < seg->clocktime_wrap_duration)
                seg->cut_pending = 1;
            seg->last_val = wrapped_val;
        } else {
            end_pts = seg->time * (seg->segment_count + 1);
        }
    }

    ff_dlog(s, "packet stream:%d pts:%s pts_time:%s duration_time:%s is_key:%d frame:%d\n",
            pkt->stream_index, av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, &st->time_base),
            av_ts2timestr(pkt->duration, &st->time_base),
            pkt->flags & AV_PKT_FLAG_KEY,
            pkt->stream_index == seg->reference_stream_index ? seg->frame_count : -1);

    if (pkt->stream_index == seg->reference_stream_index &&
        (pkt->flags & AV_PKT_FLAG_KEY || seg->break_non_keyframes) &&
        (seg->segment_frame_count > 0 || seg->write_empty) &&
        (seg->cut_pending || seg->frame_count >= start_frame ||
         (pkt->pts != AV_NOPTS_VALUE &&
          av_compare_ts(pkt->pts, st->time_base,
                        end_pts - seg->time_delta, AV_TIME_BASE_Q) >= 0))) {
        /* sanitize end time in case last packet didn't have a defined duration */
        if (seg->cur_entry.last_duration == 0)
            seg->cur_entry.end_time = (double)pkt->pts * av_q2d(st->time_base);

        if ((ret = segment_end(s, seg->individual_header_trailer, 0)) < 0)
            goto fail;

        if ((ret = segment_start(s, seg->individual_header_trailer)) < 0)
            goto fail;

        seg->cut_pending = 0;
        seg->cur_entry.index = seg->segment_idx + seg->segment_idx_wrap * seg->segment_idx_wrap_nb;
        seg->cur_entry.start_time = (double)pkt->pts * av_q2d(st->time_base);
        seg->cur_entry.start_pts = av_rescale_q(pkt->pts, st->time_base, AV_TIME_BASE_Q);
        seg->cur_entry.end_time = seg->cur_entry.start_time;

        if (seg->times || (!seg->frames && !seg->use_clocktime) && seg->write_empty)
            goto calc_times;
    }

    if (pkt->stream_index == seg->reference_stream_index) {
        if (pkt->pts != AV_NOPTS_VALUE)
            seg->cur_entry.end_time =
                FFMAX(seg->cur_entry.end_time, (double)(pkt->pts + pkt->duration) * av_q2d(st->time_base));
        seg->cur_entry.last_duration = pkt->duration;
    }

    if (seg->segment_frame_count == 0) {
        av_log(s, AV_LOG_VERBOSE, "segment:'%s' starts with packet stream:%d pts:%s pts_time:%s frame:%d\n",
               seg->avf->url, pkt->stream_index,
               av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, &st->time_base), seg->frame_count);
    }

    av_log(s, AV_LOG_DEBUG, "stream:%d start_pts_time:%s pts:%s pts_time:%s dts:%s dts_time:%s",
           pkt->stream_index,
           av_ts2timestr(seg->cur_entry.start_pts, &AV_TIME_BASE_Q),
           av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, &st->time_base),
           av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, &st->time_base));

    /* compute new timestamps */
    offset = av_rescale_q(seg->initial_offset - (seg->reset_timestamps ? seg->cur_entry.start_pts : 0),
                          AV_TIME_BASE_Q, st->time_base);
    if (pkt->pts != AV_NOPTS_VALUE)
        pkt->pts += offset;
    if (pkt->dts != AV_NOPTS_VALUE)
        pkt->dts += offset;

    av_log(s, AV_LOG_DEBUG, " -> pts:%s pts_time:%s dts:%s dts_time:%s\n",
           av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, &st->time_base),
           av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, &st->time_base));

    ret = ff_write_chained(seg->avf, pkt->stream_index, pkt, s, seg->initial_offset || seg->reset_timestamps);

fail:
    if (pkt->stream_index == seg->reference_stream_index) {
        seg->frame_count++;
        seg->segment_frame_count++;
    }

    return ret;
}