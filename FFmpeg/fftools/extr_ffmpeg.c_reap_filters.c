#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  double int64_t ;
typedef  int /*<<< orphan*/  error ;
struct TYPE_33__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_35__ {int /*<<< orphan*/  channels; TYPE_4__* codec; TYPE_7__ time_base; int /*<<< orphan*/  sample_aspect_ratio; } ;
struct TYPE_34__ {double pts; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_aspect_ratio; } ;
struct TYPE_32__ {double start_time; } ;
struct TYPE_29__ {int /*<<< orphan*/  num; } ;
struct TYPE_31__ {size_t file_index; TYPE_3__ frame_aspect_ratio; scalar_t__ finished; TYPE_8__* filtered_frame; int /*<<< orphan*/  index; int /*<<< orphan*/  initialized; TYPE_2__* filter; TYPE_9__* enc_ctx; } ;
struct TYPE_30__ {int capabilities; } ;
struct TYPE_28__ {int /*<<< orphan*/ * filter; TYPE_1__* graph; } ;
struct TYPE_27__ {int /*<<< orphan*/  graph; } ;
typedef  TYPE_5__ OutputStream ;
typedef  TYPE_6__ OutputFile ;
typedef  TYPE_7__ AVRational ;
typedef  TYPE_8__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_BUFFERSINK_FLAG_NO_REQUEST ; 
 int AV_CODEC_CAP_PARAM_CHANGE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 double AV_NOPTS_VALUE ; 
 TYPE_7__ AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 double FFSIGN (double) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int av_buffersink_get_frame_flags (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_7__ av_buffersink_get_time_base (int /*<<< orphan*/ *) ; 
 int av_buffersink_get_type (int /*<<< orphan*/ *) ; 
 int av_clip (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 TYPE_8__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_8__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_log2 (int) ; 
 void* av_rescale_q (double,TYPE_7__,TYPE_7__) ; 
 int /*<<< orphan*/  av_ts2str (double) ; 
 int /*<<< orphan*/  av_ts2timestr (double,TYPE_7__*) ; 
 int /*<<< orphan*/  debug_ts ; 
 int /*<<< orphan*/  do_audio_out (TYPE_6__*,TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  do_video_out (TYPE_6__*,TYPE_5__*,TYPE_8__*,double) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int init_output_stream (TYPE_5__*,char*,int) ; 
 int nb_output_streams ; 
 TYPE_6__** output_files ; 
 TYPE_5__** output_streams ; 

__attribute__((used)) static int reap_filters(int flush)
{
    AVFrame *filtered_frame = NULL;
    int i;

    /* Reap all buffers present in the buffer sinks */
    for (i = 0; i < nb_output_streams; i++) {
        OutputStream *ost = output_streams[i];
        OutputFile    *of = output_files[ost->file_index];
        AVFilterContext *filter;
        AVCodecContext *enc = ost->enc_ctx;
        int ret = 0;

        if (!ost->filter || !ost->filter->graph->graph)
            continue;
        filter = ost->filter->filter;

        if (!ost->initialized) {
            char error[1024] = "";
            ret = init_output_stream(ost, error, sizeof(error));
            if (ret < 0) {
                av_log(NULL, AV_LOG_ERROR, "Error initializing output stream %d:%d -- %s\n",
                       ost->file_index, ost->index, error);
                exit_program(1);
            }
        }

        if (!ost->filtered_frame && !(ost->filtered_frame = av_frame_alloc())) {
            return AVERROR(ENOMEM);
        }
        filtered_frame = ost->filtered_frame;

        while (1) {
            double float_pts = AV_NOPTS_VALUE; // this is identical to filtered_frame.pts but with higher precision
            ret = av_buffersink_get_frame_flags(filter, filtered_frame,
                                               AV_BUFFERSINK_FLAG_NO_REQUEST);
            if (ret < 0) {
                if (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
                    av_log(NULL, AV_LOG_WARNING,
                           "Error in av_buffersink_get_frame_flags(): %s\n", av_err2str(ret));
                } else if (flush && ret == AVERROR_EOF) {
                    if (av_buffersink_get_type(filter) == AVMEDIA_TYPE_VIDEO)
                        do_video_out(of, ost, NULL, AV_NOPTS_VALUE);
                }
                break;
            }
            if (ost->finished) {
                av_frame_unref(filtered_frame);
                continue;
            }
            if (filtered_frame->pts != AV_NOPTS_VALUE) {
                int64_t start_time = (of->start_time == AV_NOPTS_VALUE) ? 0 : of->start_time;
                AVRational filter_tb = av_buffersink_get_time_base(filter);
                AVRational tb = enc->time_base;
                int extra_bits = av_clip(29 - av_log2(tb.den), 0, 16);

                tb.den <<= extra_bits;
                float_pts =
                    av_rescale_q(filtered_frame->pts, filter_tb, tb) -
                    av_rescale_q(start_time, AV_TIME_BASE_Q, tb);
                float_pts /= 1 << extra_bits;
                // avoid exact midoints to reduce the chance of rounding differences, this can be removed in case the fps code is changed to work with integers
                float_pts += FFSIGN(float_pts) * 1.0 / (1<<17);

                filtered_frame->pts =
                    av_rescale_q(filtered_frame->pts, filter_tb, enc->time_base) -
                    av_rescale_q(start_time, AV_TIME_BASE_Q, enc->time_base);
            }

            switch (av_buffersink_get_type(filter)) {
            case AVMEDIA_TYPE_VIDEO:
                if (!ost->frame_aspect_ratio.num)
                    enc->sample_aspect_ratio = filtered_frame->sample_aspect_ratio;

                if (debug_ts) {
                    av_log(NULL, AV_LOG_INFO, "filter -> pts:%s pts_time:%s exact:%f time_base:%d/%d\n",
                            av_ts2str(filtered_frame->pts), av_ts2timestr(filtered_frame->pts, &enc->time_base),
                            float_pts,
                            enc->time_base.num, enc->time_base.den);
                }

                do_video_out(of, ost, filtered_frame, float_pts);
                break;
            case AVMEDIA_TYPE_AUDIO:
                if (!(enc->codec->capabilities & AV_CODEC_CAP_PARAM_CHANGE) &&
                    enc->channels != filtered_frame->channels) {
                    av_log(NULL, AV_LOG_ERROR,
                           "Audio filter graph output is not normalized and encoder does not support parameter changes\n");
                    break;
                }
                do_audio_out(of, ost, filtered_frame);
                break;
            default:
                // TODO support subtitle filters
                av_assert0(0);
            }

            av_frame_unref(filtered_frame);
        }
    }

    return 0;
}