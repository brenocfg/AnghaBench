#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {scalar_t__ seekable; } ;
struct TYPE_28__ {int (* io_open ) (TYPE_5__*,TYPE_7__**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int nb_streams; scalar_t__ avoid_negative_ts; TYPE_4__** streams; TYPE_7__* pb; scalar_t__ url; TYPE_3__* priv_data; } ;
struct TYPE_25__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_27__ {TYPE_2__ time_base; int /*<<< orphan*/  pts_wrap_bits; TYPE_1__* codecpar; } ;
struct TYPE_26__ {int write_header_trailer; scalar_t__ initial_offset; int time; int clocktime_offset; scalar_t__ list_type; size_t reference_stream_index; int header_written; scalar_t__ segment_frame_count; scalar_t__ format_options_str; int /*<<< orphan*/  format_options; scalar_t__ individual_header_trailer; scalar_t__ header_filename; TYPE_5__* avf; TYPE_22__* oformat; int /*<<< orphan*/  format; int /*<<< orphan*/  use_rename; scalar_t__ list; int /*<<< orphan*/  list_size; scalar_t__ use_clocktime; scalar_t__ time_str; scalar_t__ frames_str; int /*<<< orphan*/  nb_frames; int /*<<< orphan*/  frames; scalar_t__ times_str; int /*<<< orphan*/  nb_times; int /*<<< orphan*/  times; scalar_t__ segment_count; } ;
struct TYPE_24__ {int flags; scalar_t__ name; } ;
struct TYPE_23__ {int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ SegmentContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_MUXER_NOT_FOUND ; 
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int AVSTREAM_INIT_IN_WRITE_HEADER ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ LIST_TYPE_CSV ; 
 scalar_t__ LIST_TYPE_EXT ; 
 scalar_t__ LIST_TYPE_FFCONCAT ; 
 scalar_t__ LIST_TYPE_FLAT ; 
 scalar_t__ LIST_TYPE_M3U8 ; 
 scalar_t__ LIST_TYPE_UNDEFINED ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ av_dict_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int av_dict_parse_string (int /*<<< orphan*/ *,scalar_t__,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_get_media_type_string (int /*<<< orphan*/ ) ; 
 TYPE_22__* av_guess_format (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_match_ext (scalar_t__,char*) ; 
 int av_parse_time (int*,scalar_t__,int) ; 
 scalar_t__ av_strdup (char*) ; 
 int avformat_init_output (TYPE_5__*,int /*<<< orphan*/ **) ; 
 int avformat_write_header (TYPE_5__*,int /*<<< orphan*/ *) ; 
 char* avio_find_protocol_name (scalar_t__) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_5__*,TYPE_7__**) ; 
 int open_null_ctx (TYPE_7__**) ; 
 int parse_frames (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int parse_times (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int segment_list_open (TYPE_5__*) ; 
 int segment_mux_init (TYPE_5__*) ; 
 int select_reference_stream (TYPE_5__*) ; 
 int set_segment_filename (TYPE_5__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int stub1 (TYPE_5__*,TYPE_7__**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seg_init(AVFormatContext *s)
{
    SegmentContext *seg = s->priv_data;
    AVFormatContext *oc = seg->avf;
    AVDictionary *options = NULL;
    int ret;
    int i;

    seg->segment_count = 0;
    if (!seg->write_header_trailer)
        seg->individual_header_trailer = 0;

    if (seg->header_filename) {
        seg->write_header_trailer = 1;
        seg->individual_header_trailer = 0;
    }

    if (seg->initial_offset > 0) {
        av_log(s, AV_LOG_WARNING, "NOTE: the option initial_offset is deprecated,"
               "you can use output_ts_offset instead of it\n");
    }

    if (!!seg->time_str + !!seg->times_str + !!seg->frames_str > 1) {
        av_log(s, AV_LOG_ERROR,
               "segment_time, segment_times, and segment_frames options "
               "are mutually exclusive, select just one of them\n");
        return AVERROR(EINVAL);
    }

    if (seg->times_str) {
        if ((ret = parse_times(s, &seg->times, &seg->nb_times, seg->times_str)) < 0)
            return ret;
    } else if (seg->frames_str) {
        if ((ret = parse_frames(s, &seg->frames, &seg->nb_frames, seg->frames_str)) < 0)
            return ret;
    } else {
        /* set default value if not specified */
        if (!seg->time_str)
            seg->time_str = av_strdup("2");
        if ((ret = av_parse_time(&seg->time, seg->time_str, 1)) < 0) {
            av_log(s, AV_LOG_ERROR,
                   "Invalid time duration specification '%s' for segment_time option\n",
                   seg->time_str);
            return ret;
        }
        if (seg->use_clocktime) {
            if (seg->time <= 0) {
                av_log(s, AV_LOG_ERROR, "Invalid negative segment_time with segment_atclocktime option set\n");
                return AVERROR(EINVAL);
            }
            seg->clocktime_offset = seg->time - (seg->clocktime_offset % seg->time);
        }
    }

    if (seg->format_options_str) {
        ret = av_dict_parse_string(&seg->format_options, seg->format_options_str, "=", ":", 0);
        if (ret < 0) {
            av_log(s, AV_LOG_ERROR, "Could not parse format options list '%s'\n",
                   seg->format_options_str);
            return ret;
        }
    }

    if (seg->list) {
        if (seg->list_type == LIST_TYPE_UNDEFINED) {
            if      (av_match_ext(seg->list, "csv" )) seg->list_type = LIST_TYPE_CSV;
            else if (av_match_ext(seg->list, "ext" )) seg->list_type = LIST_TYPE_EXT;
            else if (av_match_ext(seg->list, "m3u8")) seg->list_type = LIST_TYPE_M3U8;
            else if (av_match_ext(seg->list, "ffcat,ffconcat")) seg->list_type = LIST_TYPE_FFCONCAT;
            else                                      seg->list_type = LIST_TYPE_FLAT;
        }
        if (!seg->list_size && seg->list_type != LIST_TYPE_M3U8) {
            if ((ret = segment_list_open(s)) < 0)
                return ret;
        } else {
            const char *proto = avio_find_protocol_name(seg->list);
            seg->use_rename = proto && !strcmp(proto, "file");
        }
    }

    if (seg->list_type == LIST_TYPE_EXT)
        av_log(s, AV_LOG_WARNING, "'ext' list type option is deprecated in favor of 'csv'\n");

    if ((ret = select_reference_stream(s)) < 0)
        return ret;
    av_log(s, AV_LOG_VERBOSE, "Selected stream id:%d type:%s\n",
           seg->reference_stream_index,
           av_get_media_type_string(s->streams[seg->reference_stream_index]->codecpar->codec_type));

    seg->oformat = av_guess_format(seg->format, s->url, NULL);

    if (!seg->oformat)
        return AVERROR_MUXER_NOT_FOUND;
    if (seg->oformat->flags & AVFMT_NOFILE) {
        av_log(s, AV_LOG_ERROR, "format %s not supported.\n",
               seg->oformat->name);
        return AVERROR(EINVAL);
    }

    if ((ret = segment_mux_init(s)) < 0)
        return ret;

    if ((ret = set_segment_filename(s)) < 0)
        return ret;
    oc = seg->avf;

    if (seg->write_header_trailer) {
        if ((ret = s->io_open(s, &oc->pb,
                              seg->header_filename ? seg->header_filename : oc->url,
                              AVIO_FLAG_WRITE, NULL)) < 0) {
            av_log(s, AV_LOG_ERROR, "Failed to open segment '%s'\n", oc->url);
            return ret;
        }
        if (!seg->individual_header_trailer)
            oc->pb->seekable = 0;
    } else {
        if ((ret = open_null_ctx(&oc->pb)) < 0)
            return ret;
    }

    av_dict_copy(&options, seg->format_options, 0);
    av_dict_set(&options, "fflags", "-autobsf", 0);
    ret = avformat_init_output(oc, &options);
    if (av_dict_count(options)) {
        av_log(s, AV_LOG_ERROR,
               "Some of the provided format options in '%s' are not recognized\n", seg->format_options_str);
        av_dict_free(&options);
        return AVERROR(EINVAL);
    }
    av_dict_free(&options);

    if (ret < 0) {
        ff_format_io_close(oc, &oc->pb);
        return ret;
    }
    seg->segment_frame_count = 0;

    av_assert0(s->nb_streams == oc->nb_streams);
    if (ret == AVSTREAM_INIT_IN_WRITE_HEADER) {
        ret = avformat_write_header(oc, NULL);
        if (ret < 0)
            return ret;
        seg->header_written = 1;
    }

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *inner_st  = oc->streams[i];
        AVStream *outer_st = s->streams[i];
        avpriv_set_pts_info(outer_st, inner_st->pts_wrap_bits, inner_st->time_base.num, inner_st->time_base.den);
    }

    if (oc->avoid_negative_ts > 0 && s->avoid_negative_ts < 0)
        s->avoid_negative_ts = 1;

    return ret;
}