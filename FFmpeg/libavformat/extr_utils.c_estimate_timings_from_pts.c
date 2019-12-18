#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_23__ {int nb_streams; TYPE_4__** streams; scalar_t__ pb; scalar_t__ skip_estimate_duration_from_pts; } ;
struct TYPE_22__ {size_t stream_index; scalar_t__ pts; scalar_t__ duration; scalar_t__ size; } ;
struct TYPE_18__ {long long den; long long num; } ;
struct TYPE_21__ {scalar_t__ start_time; scalar_t__ first_dts; scalar_t__ duration; scalar_t__ cur_dts; scalar_t__* pts_buffer; scalar_t__ last_dts_for_order_check; scalar_t__ last_IP_pts; TYPE_3__* codecpar; TYPE_2__* info; TYPE_1__ time_base; int /*<<< orphan*/ * parser; } ;
struct TYPE_20__ {int codec_type; } ;
struct TYPE_19__ {scalar_t__ last_duration; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AVMEDIA_TYPE_AUDIO 129 
 int AVMEDIA_TYPE_UNKNOWN ; 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int /*<<< orphan*/  AV_ROUND_DOWN ; 
 int DURATION_MAX_READ_SIZE ; 
 int DURATION_MAX_RETRY ; 
 int /*<<< orphan*/  EAGAIN ; 
 long long FFABS (int) ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int MAX_REORDER_DELAY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_opt_set (TYPE_6__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int /*<<< orphan*/  av_parser_close (int /*<<< orphan*/ *) ; 
 scalar_t__ av_rescale_rnd (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int avio_size (scalar_t__) ; 
 int /*<<< orphan*/  ff_compute_frame_duration (TYPE_6__*,int*,int*,TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int ff_read_packet (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  fill_all_stream_timings (TYPE_6__*) ; 
 int /*<<< orphan*/  flush_packet_queue (TYPE_6__*) ; 

__attribute__((used)) static void estimate_timings_from_pts(AVFormatContext *ic, int64_t old_offset)
{
    AVPacket pkt1, *pkt = &pkt1;
    AVStream *st;
    int num, den, read_size, i, ret;
    int found_duration = 0;
    int is_end;
    int64_t filesize, offset, duration;
    int retry = 0;

    /* flush packet queue */
    flush_packet_queue(ic);

    for (i = 0; i < ic->nb_streams; i++) {
        st = ic->streams[i];
        if (st->start_time == AV_NOPTS_VALUE &&
            st->first_dts == AV_NOPTS_VALUE &&
            st->codecpar->codec_type != AVMEDIA_TYPE_UNKNOWN)
            av_log(ic, AV_LOG_WARNING,
                   "start time for stream %d is not set in estimate_timings_from_pts\n", i);

        if (st->parser) {
            av_parser_close(st->parser);
            st->parser = NULL;
        }
    }

    if (ic->skip_estimate_duration_from_pts) {
        av_log(ic, AV_LOG_INFO, "Skipping duration calculation in estimate_timings_from_pts\n");
        goto skip_duration_calc;
    }

    av_opt_set(ic, "skip_changes", "1", AV_OPT_SEARCH_CHILDREN);
    /* estimate the end time (duration) */
    /* XXX: may need to support wrapping */
    filesize = ic->pb ? avio_size(ic->pb) : 0;
    do {
        is_end = found_duration;
        offset = filesize - (DURATION_MAX_READ_SIZE << retry);
        if (offset < 0)
            offset = 0;

        avio_seek(ic->pb, offset, SEEK_SET);
        read_size = 0;
        for (;;) {
            if (read_size >= DURATION_MAX_READ_SIZE << (FFMAX(retry - 1, 0)))
                break;

            do {
                ret = ff_read_packet(ic, pkt);
            } while (ret == AVERROR(EAGAIN));
            if (ret != 0)
                break;
            read_size += pkt->size;
            st         = ic->streams[pkt->stream_index];
            if (pkt->pts != AV_NOPTS_VALUE &&
                (st->start_time != AV_NOPTS_VALUE ||
                 st->first_dts  != AV_NOPTS_VALUE)) {
                if (pkt->duration == 0) {
                    ff_compute_frame_duration(ic, &num, &den, st, st->parser, pkt);
                    if (den && num) {
                        pkt->duration = av_rescale_rnd(1,
                                           num * (int64_t) st->time_base.den,
                                           den * (int64_t) st->time_base.num,
                                           AV_ROUND_DOWN);
                    }
                }
                duration = pkt->pts + pkt->duration;
                found_duration = 1;
                if (st->start_time != AV_NOPTS_VALUE)
                    duration -= st->start_time;
                else
                    duration -= st->first_dts;
                if (duration > 0) {
                    if (st->duration == AV_NOPTS_VALUE || st->info->last_duration<= 0 ||
                        (st->duration < duration && FFABS(duration - st->info->last_duration) < 60LL*st->time_base.den / st->time_base.num))
                        st->duration = duration;
                    st->info->last_duration = duration;
                }
            }
            av_packet_unref(pkt);
        }

        /* check if all audio/video streams have valid duration */
        if (!is_end) {
            is_end = 1;
            for (i = 0; i < ic->nb_streams; i++) {
                st = ic->streams[i];
                switch (st->codecpar->codec_type) {
                    case AVMEDIA_TYPE_VIDEO:
                    case AVMEDIA_TYPE_AUDIO:
                        if (st->duration == AV_NOPTS_VALUE)
                            is_end = 0;
                }
            }
        }
    } while (!is_end &&
             offset &&
             ++retry <= DURATION_MAX_RETRY);

    av_opt_set(ic, "skip_changes", "0", AV_OPT_SEARCH_CHILDREN);

    /* warn about audio/video streams which duration could not be estimated */
    for (i = 0; i < ic->nb_streams; i++) {
        st = ic->streams[i];
        if (st->duration == AV_NOPTS_VALUE) {
            switch (st->codecpar->codec_type) {
            case AVMEDIA_TYPE_VIDEO:
            case AVMEDIA_TYPE_AUDIO:
                if (st->start_time != AV_NOPTS_VALUE || st->first_dts  != AV_NOPTS_VALUE) {
                    av_log(ic, AV_LOG_WARNING, "stream %d : no PTS found at end of file, duration not set\n", i);
                } else
                    av_log(ic, AV_LOG_WARNING, "stream %d : no TS found at start of file, duration not set\n", i);
            }
        }
    }
skip_duration_calc:
    fill_all_stream_timings(ic);

    avio_seek(ic->pb, old_offset, SEEK_SET);
    for (i = 0; i < ic->nb_streams; i++) {
        int j;

        st              = ic->streams[i];
        st->cur_dts     = st->first_dts;
        st->last_IP_pts = AV_NOPTS_VALUE;
        st->last_dts_for_order_check = AV_NOPTS_VALUE;
        for (j = 0; j < MAX_REORDER_DELAY + 1; j++)
            st->pts_buffer[j] = AV_NOPTS_VALUE;
    }
}