#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_29__ {scalar_t__ avoid_negative_ts; int /*<<< orphan*/  url; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_28__ {size_t stream_index; int duration; int dts; int pts; int flags; scalar_t__ size; } ;
struct TYPE_27__ {int /*<<< orphan*/  time_base; TYPE_10__* codecpar; int /*<<< orphan*/  avg_frame_rate; } ;
struct TYPE_26__ {int start_time_s; int seg_duration; int last_duration; char* dirname; scalar_t__ streaming; scalar_t__ lhls; int /*<<< orphan*/  single_file; scalar_t__ use_template; int /*<<< orphan*/  use_timeline; void* total_duration; int /*<<< orphan*/  has_video; int /*<<< orphan*/ * availability_start_time; TYPE_1__* streams; } ;
struct TYPE_25__ {scalar_t__ last_dts; scalar_t__ first_pts; int last_pts; double availability_time_offset; int start_pts; int packets_written; scalar_t__ max_pts; char* filename; char* full_path; char* temp_path; scalar_t__ segment_type; int written_len; scalar_t__ out; TYPE_15__* ctx; int /*<<< orphan*/  bit_rate; scalar_t__ segment_index; int /*<<< orphan*/  media_seg_name; int /*<<< orphan*/  init_range_length; int /*<<< orphan*/  total_pkt_size; } ;
struct TYPE_24__ {scalar_t__ pb; } ;
struct TYPE_23__ {scalar_t__ codec_type; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ DASHContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 scalar_t__ AVFMT_AVOID_NEG_TS_MAKE_ZERO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 double AV_TIME_BASE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int FFMAX (int,int) ; 
 scalar_t__ SEGMENT_TYPE_MP4 ; 
 scalar_t__ av_compare_ts (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 void* av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* avio_find_protocol_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_flush (scalar_t__) ; 
 int avio_get_dyn_buf (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int dash_flush (TYPE_5__*,int /*<<< orphan*/ ,size_t) ; 
 int dashenc_io_open (TYPE_5__*,scalar_t__*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_dash_fill_tmpl_params (char*,int,int /*<<< orphan*/ ,size_t,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int ff_write_chained (TYPE_15__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_init_segment (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  format_date_now (int /*<<< orphan*/ *,int) ; 
 int handle_io_open_error (TYPE_5__*,int,char*) ; 
 int /*<<< orphan*/  set_http_options (int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int update_stream_extradata (TYPE_5__*,TYPE_1__*,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_hls_media_playlist (TYPE_1__*,TYPE_5__*,size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_styp (scalar_t__) ; 

__attribute__((used)) static int dash_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    DASHContext *c = s->priv_data;
    AVStream *st = s->streams[pkt->stream_index];
    OutputStream *os = &c->streams[pkt->stream_index];
    int64_t seg_end_duration, elapsed_duration;
    int ret;

    ret = update_stream_extradata(s, os, st->codecpar, &st->avg_frame_rate);
    if (ret < 0)
        return ret;

    // Fill in a heuristic guess of the packet duration, if none is available.
    // The mp4 muxer will do something similar (for the last packet in a fragment)
    // if nothing is set (setting it for the other packets doesn't hurt).
    // By setting a nonzero duration here, we can be sure that the mp4 muxer won't
    // invoke its heuristic (this doesn't have to be identical to that algorithm),
    // so that we know the exact timestamps of fragments.
    if (!pkt->duration && os->last_dts != AV_NOPTS_VALUE)
        pkt->duration = pkt->dts - os->last_dts;
    os->last_dts = pkt->dts;

    // If forcing the stream to start at 0, the mp4 muxer will set the start
    // timestamps to 0. Do the same here, to avoid mismatches in duration/timestamps.
    if (os->first_pts == AV_NOPTS_VALUE &&
        s->avoid_negative_ts == AVFMT_AVOID_NEG_TS_MAKE_ZERO) {
        pkt->pts -= pkt->dts;
        pkt->dts  = 0;
    }

    if (os->first_pts == AV_NOPTS_VALUE)
        os->first_pts = pkt->pts;
    os->last_pts = pkt->pts;

    if (!c->availability_start_time[0]) {
        int64_t start_time_us = av_gettime();
        c->start_time_s = start_time_us / 1000000;
        format_date_now(c->availability_start_time,
                        sizeof(c->availability_start_time));
    }

    if (!os->availability_time_offset && pkt->duration) {
        int64_t frame_duration = av_rescale_q(pkt->duration, st->time_base,
                                              AV_TIME_BASE_Q);
         os->availability_time_offset = ((double) c->seg_duration -
                                         frame_duration) / AV_TIME_BASE;
    }

    if (c->use_template && !c->use_timeline) {
        elapsed_duration = pkt->pts - os->first_pts;
        seg_end_duration = (int64_t) os->segment_index * c->seg_duration;
    } else {
        elapsed_duration = pkt->pts - os->start_pts;
        seg_end_duration = c->seg_duration;
    }

    if ((!c->has_video || st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) &&
        pkt->flags & AV_PKT_FLAG_KEY && os->packets_written &&
        av_compare_ts(elapsed_duration, st->time_base,
                      seg_end_duration, AV_TIME_BASE_Q) >= 0) {
        int64_t prev_duration = c->last_duration;

        c->last_duration = av_rescale_q(pkt->pts - os->start_pts,
                                        st->time_base,
                                        AV_TIME_BASE_Q);
        c->total_duration = av_rescale_q(pkt->pts - os->first_pts,
                                         st->time_base,
                                         AV_TIME_BASE_Q);

        if ((!c->use_timeline || !c->use_template) && prev_duration) {
            if (c->last_duration < prev_duration*9/10 ||
                c->last_duration > prev_duration*11/10) {
                av_log(s, AV_LOG_WARNING,
                       "Segment durations differ too much, enable use_timeline "
                       "and use_template, or keep a stricter keyframe interval\n");
            }
        }

        if ((ret = dash_flush(s, 0, pkt->stream_index)) < 0)
            return ret;
    }

    if (!os->packets_written) {
        // If we wrote a previous segment, adjust the start time of the segment
        // to the end of the previous one (which is the same as the mp4 muxer
        // does). This avoids gaps in the timeline.
        if (os->max_pts != AV_NOPTS_VALUE)
            os->start_pts = os->max_pts;
        else
            os->start_pts = pkt->pts;
    }
    if (os->max_pts == AV_NOPTS_VALUE)
        os->max_pts = pkt->pts + pkt->duration;
    else
        os->max_pts = FFMAX(os->max_pts, pkt->pts + pkt->duration);
    os->packets_written++;
    os->total_pkt_size += pkt->size;
    if ((ret = ff_write_chained(os->ctx, 0, pkt, s, 0)) < 0)
        return ret;

    if (!os->init_range_length)
        flush_init_segment(s, os);

    //open the output context when the first frame of a segment is ready
    if (!c->single_file && os->packets_written == 1) {
        AVDictionary *opts = NULL;
        const char *proto = avio_find_protocol_name(s->url);
        int use_rename = proto && !strcmp(proto, "file");
        os->filename[0] = os->full_path[0] = os->temp_path[0] = '\0';
        ff_dash_fill_tmpl_params(os->filename, sizeof(os->filename),
                                 os->media_seg_name, pkt->stream_index,
                                 os->segment_index, os->bit_rate, os->start_pts);
        snprintf(os->full_path, sizeof(os->full_path), "%s%s", c->dirname,
                 os->filename);
        snprintf(os->temp_path, sizeof(os->temp_path),
                 use_rename ? "%s.tmp" : "%s", os->full_path);
        set_http_options(&opts, c);
        ret = dashenc_io_open(s, &os->out, os->temp_path, &opts);
        av_dict_free(&opts);
        if (ret < 0) {
            return handle_io_open_error(s, ret, os->temp_path);
        }
        if (c->lhls) {
            char *prefetch_url = use_rename ? NULL : os->filename;
            write_hls_media_playlist(os, s, pkt->stream_index, 0, prefetch_url);
        }
    }

    //write out the data immediately in streaming mode
    if (c->streaming && os->segment_type == SEGMENT_TYPE_MP4) {
        int len = 0;
        uint8_t *buf = NULL;
        if (!os->written_len)
            write_styp(os->ctx->pb);
        avio_flush(os->ctx->pb);
        len = avio_get_dyn_buf (os->ctx->pb, &buf);
        if (os->out) {
            avio_write(os->out, buf + os->written_len, len - os->written_len);
            avio_flush(os->out);
        }
        os->written_len = len;
    }

    return ret;
}