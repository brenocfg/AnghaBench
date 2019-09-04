#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_33__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  void* int64_t ;
struct TYPE_37__ {int nb_streams; int number; scalar_t__ sequence; int nb_entries; scalar_t__ start_pts; scalar_t__ reference_stream_index; scalar_t__ end_pts; double duration; double dpp; int size; void* start_pos; int init_range_length; scalar_t__ packets_written; TYPE_7__* avf; scalar_t__ out; TYPE_7__* vtt_avf; scalar_t__* base_output_dirname; scalar_t__ new_start; scalar_t__ has_video; TYPE_5__** streams; } ;
typedef  TYPE_3__ VariantStream ;
struct TYPE_41__ {scalar_t__ pb; scalar_t__* url; TYPE_4__* priv_data; TYPE_2__* oformat; TYPE_5__** streams; } ;
struct TYPE_40__ {size_t stream_index; scalar_t__ pts; int flags; scalar_t__ duration; } ;
struct TYPE_36__ {double num; double den; } ;
struct TYPE_39__ {TYPE_33__ time_base; TYPE_1__* codecpar; } ;
struct TYPE_38__ {int nb_varstreams; int recording_time; scalar_t__ start_sequence; int init_time; int time; int flags; int max_seg_size; scalar_t__ segment_type; scalar_t__ pl_type; scalar_t__ ignore_io_errors; TYPE_3__* var_streams; } ;
struct TYPE_35__ {scalar_t__ priv_class; } ;
struct TYPE_34__ {scalar_t__ codec_type; } ;
typedef  TYPE_4__ HLSContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HLS_SINGLE_FILE ; 
 int HLS_SPLIT_BY_TIME ; 
 int HLS_TEMP_FILE ; 
 scalar_t__ PLAYLIST_TYPE_VOD ; 
 scalar_t__ SEGMENT_TYPE_FMP4 ; 
 scalar_t__ av_compare_ts (scalar_t__,TYPE_33__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_opt_set (TYPE_4__*,char*,char*,int /*<<< orphan*/ ) ; 
 char* av_strdup (scalar_t__*) ; 
 int /*<<< orphan*/  av_write_frame (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (scalar_t__,char**) ; 
 char* avio_find_protocol_name (scalar_t__*) ; 
 int /*<<< orphan*/  avio_flush (scalar_t__) ; 
 int /*<<< orphan*/  avio_open_dyn_buf (scalar_t__*) ; 
 void* avio_tell (scalar_t__) ; 
 int /*<<< orphan*/  avio_write (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_7__*,scalar_t__*) ; 
 int ff_write_chained (TYPE_7__*,int,TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int flush_dynbuf (TYPE_3__*,int*) ; 
 int hls_append_segment (TYPE_7__*,TYPE_4__*,TYPE_3__*,double,int,int) ; 
 int /*<<< orphan*/  hls_rename_temp_file (TYPE_7__*,TYPE_7__*) ; 
 int hls_start (TYPE_7__*,TYPE_3__*) ; 
 int hls_window (TYPE_7__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  hlsenc_io_close (TYPE_7__*,scalar_t__*,scalar_t__*) ; 
 int hlsenc_io_open (TYPE_7__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_http_options (TYPE_7__*,int /*<<< orphan*/ **,TYPE_4__*) ; 
 int /*<<< orphan*/  sls_flag_file_rename (TYPE_4__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  write_styp (scalar_t__) ; 

__attribute__((used)) static int hls_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    HLSContext *hls = s->priv_data;
    AVFormatContext *oc = NULL;
    AVStream *st = s->streams[pkt->stream_index];
    int64_t end_pts = 0;
    int is_ref_pkt = 1;
    int ret = 0, can_split = 1, i, j;
    int stream_index = 0;
    int range_length = 0;
    const char *proto = NULL;
    int use_temp_file = 0;
    uint8_t *buffer = NULL;
    VariantStream *vs = NULL;
    AVDictionary *options = NULL;
    char *old_filename = NULL;

    for (i = 0; i < hls->nb_varstreams; i++) {
        vs = &hls->var_streams[i];
        for (j = 0; j < vs->nb_streams; j++) {
            if (vs->streams[j] == st) {
                if( st->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE ) {
                    oc = vs->vtt_avf;
                    stream_index = 0;
                } else {
                    oc = vs->avf;
                    stream_index = j;
                }
                break;
            }
        }

        if (oc)
            break;
    }

    if (!oc) {
        av_log(s, AV_LOG_ERROR, "Unable to find mapping variant stream\n");
        return AVERROR(ENOMEM);
    }

    end_pts = hls->recording_time * vs->number;

    if (vs->sequence - vs->nb_entries > hls->start_sequence && hls->init_time > 0) {
        /* reset end_pts, hls->recording_time at end of the init hls list */
        int init_list_dur = hls->init_time * vs->nb_entries * AV_TIME_BASE;
        int after_init_list_dur = (vs->sequence - hls->start_sequence - vs->nb_entries ) * (hls->time * AV_TIME_BASE);
        hls->recording_time = hls->time * AV_TIME_BASE;
        end_pts = init_list_dur + after_init_list_dur ;
    }

    if (vs->start_pts == AV_NOPTS_VALUE) {
        vs->start_pts = pkt->pts;
    }

    if (vs->has_video) {
        can_split = st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO &&
                    ((pkt->flags & AV_PKT_FLAG_KEY) || (hls->flags & HLS_SPLIT_BY_TIME));
        is_ref_pkt = (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) && (pkt->stream_index == vs->reference_stream_index);
    }
    if (pkt->pts == AV_NOPTS_VALUE)
        is_ref_pkt = can_split = 0;

    if (is_ref_pkt) {
        if (vs->end_pts == AV_NOPTS_VALUE)
            vs->end_pts = pkt->pts;
        if (vs->new_start) {
            vs->new_start = 0;
            vs->duration = (double)(pkt->pts - vs->end_pts)
                                       * st->time_base.num / st->time_base.den;
            vs->dpp = (double)(pkt->duration) * st->time_base.num / st->time_base.den;
        } else {
            if (pkt->duration) {
                vs->duration += (double)(pkt->duration) * st->time_base.num / st->time_base.den;
            } else {
                av_log(s, AV_LOG_WARNING, "pkt->duration = 0, maybe the hls segment duration will not precise\n");
                vs->duration = (double)(pkt->pts - vs->end_pts) * st->time_base.num / st->time_base.den;
            }
        }

    }

    if (vs->packets_written && can_split && av_compare_ts(pkt->pts - vs->start_pts, st->time_base,
                                                          end_pts, AV_TIME_BASE_Q) >= 0) {
        int64_t new_start_pos;
        int byterange_mode = (hls->flags & HLS_SINGLE_FILE) || (hls->max_seg_size > 0);

        av_write_frame(vs->avf, NULL); /* Flush any buffered data */

        new_start_pos = avio_tell(vs->avf->pb);
        if (hls->segment_type != SEGMENT_TYPE_FMP4) {
            avio_flush(oc->pb);
            vs->size = new_start_pos - vs->start_pos;
        } else {
            vs->size = new_start_pos;
        }

        if (hls->segment_type == SEGMENT_TYPE_FMP4) {
            if (!vs->init_range_length) {
                avio_flush(oc->pb);
                range_length = avio_close_dyn_buf(oc->pb, &buffer);
                avio_write(vs->out, buffer, range_length);
                av_free(buffer);
                vs->init_range_length = range_length;
                avio_open_dyn_buf(&oc->pb);
                vs->packets_written = 0;
                vs->start_pos = range_length;
                if (!byterange_mode) {
                    ff_format_io_close(s, &vs->out);
                    hlsenc_io_close(s, &vs->out, vs->base_output_dirname);
                }
            }
        } else {
            if (!byterange_mode) {
                hlsenc_io_close(s, &oc->pb, oc->url);
            }
        }
        if (!byterange_mode) {
            if (vs->vtt_avf) {
                hlsenc_io_close(s, &vs->vtt_avf->pb, vs->vtt_avf->url);
            }
        }

        if (oc->url[0]) {
            proto = avio_find_protocol_name(oc->url);
            use_temp_file = proto && !strcmp(proto, "file") && (hls->flags & HLS_TEMP_FILE);
        }

        // look to rename the asset name
        if (use_temp_file) {
            if (!(hls->flags & HLS_SINGLE_FILE) || (hls->max_seg_size <= 0))
                if ((vs->avf->oformat->priv_class && vs->avf->priv_data) && hls->segment_type != SEGMENT_TYPE_FMP4)
                    av_opt_set(vs->avf->priv_data, "mpegts_flags", "resend_headers", 0);
        }

        if (hls->segment_type == SEGMENT_TYPE_FMP4) {
            if (hls->flags & HLS_SINGLE_FILE) {
                ret = flush_dynbuf(vs, &range_length);
                if (ret < 0) {
                    return ret;
                }
                vs->size = range_length;
            } else {
                set_http_options(s, &options, hls);
                ret = hlsenc_io_open(s, &vs->out, vs->avf->url, &options);
                if (ret < 0) {
                    av_log(s, hls->ignore_io_errors ? AV_LOG_WARNING : AV_LOG_ERROR,
                           "Failed to open file '%s'\n", vs->avf->url);
                    return hls->ignore_io_errors ? 0 : ret;
                }
                write_styp(vs->out);
                ret = flush_dynbuf(vs, &range_length);
                if (ret < 0) {
                    return ret;
                }
                ff_format_io_close(s, &vs->out);
            }
        }

        if (use_temp_file && !(hls->flags & HLS_SINGLE_FILE)) {
            hls_rename_temp_file(s, oc);
        }

        old_filename = av_strdup(vs->avf->url);
        if (!old_filename) {
            return AVERROR(ENOMEM);
        }

        if (vs->start_pos || hls->segment_type != SEGMENT_TYPE_FMP4) {
            ret = hls_append_segment(s, hls, vs, vs->duration, vs->start_pos, vs->size);
            vs->end_pts = pkt->pts;
            vs->duration = 0;
            if (ret < 0) {
                av_free(old_filename);
                return ret;
            }
        }

        if (hls->segment_type != SEGMENT_TYPE_FMP4) {
            vs->start_pos = new_start_pos;
        } else {
            vs->start_pos += vs->size;
        }

        if (hls->flags & HLS_SINGLE_FILE) {
            vs->number++;
        } else if (hls->max_seg_size > 0) {
            if (vs->start_pos >= hls->max_seg_size) {
                vs->sequence++;
                sls_flag_file_rename(hls, vs, old_filename);
                ret = hls_start(s, vs);
                vs->start_pos = 0;
                /* When split segment by byte, the duration is short than hls_time,
                 * so it is not enough one segment duration as hls_time, */
                vs->number--;
            }
            vs->number++;
        } else {
            sls_flag_file_rename(hls, vs, old_filename);
            ret = hls_start(s, vs);
        }
        av_free(old_filename);

        if (ret < 0) {
            return ret;
        }

        // if we're building a VOD playlist, skip writing the manifest multiple times, and just wait until the end
        if (hls->pl_type != PLAYLIST_TYPE_VOD) {
            if ((ret = hls_window(s, 0, vs)) < 0) {
                return ret;
            }
        }
    }

    vs->packets_written++;
    if (oc->pb) {
        ret = ff_write_chained(oc, stream_index, pkt, s, 0);
        if (hls->ignore_io_errors)
            ret = 0;
    }

    return ret;
}