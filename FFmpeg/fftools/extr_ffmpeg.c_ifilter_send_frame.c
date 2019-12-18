#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_28__ {scalar_t__ format; TYPE_5__* hw_frames_ctx; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_27__ {int nb_inputs; scalar_t__ graph; } ;
struct TYPE_26__ {scalar_t__ format; int /*<<< orphan*/  filter; int /*<<< orphan*/  frame_queue; TYPE_4__* hw_frames_ctx; TYPE_3__* ist; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; TYPE_7__* graph; } ;
struct TYPE_25__ {scalar_t__ data; } ;
struct TYPE_24__ {scalar_t__ data; } ;
struct TYPE_23__ {int /*<<< orphan*/  reinit_filters; TYPE_2__* st; } ;
struct TYPE_22__ {TYPE_1__* codecpar; } ;
struct TYPE_21__ {int codec_type; } ;
typedef  TYPE_6__ InputFilter ;
typedef  TYPE_7__ FilterGraph ;
typedef  TYPE_8__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_BUFFERSRC_FLAG_PUSH ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_buffersrc_add_frame_flags (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_fifo_generic_write (int /*<<< orphan*/ ,TYPE_8__**,int,int /*<<< orphan*/ *) ; 
 int av_fifo_realloc2 (int /*<<< orphan*/ ,int) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_fifo_space (int /*<<< orphan*/ ) ; 
 TYPE_8__* av_frame_clone (TYPE_8__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_8__**) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_8__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int configure_filtergraph (TYPE_7__*) ; 
 int /*<<< orphan*/  ifilter_has_all_input_formats (TYPE_7__*) ; 
 int ifilter_parameters_from_frame (TYPE_6__*,TYPE_8__*) ; 
 int reap_filters (int) ; 

__attribute__((used)) static int ifilter_send_frame(InputFilter *ifilter, AVFrame *frame)
{
    FilterGraph *fg = ifilter->graph;
    int need_reinit, ret, i;

    /* determine if the parameters for this input changed */
    need_reinit = ifilter->format != frame->format;

    switch (ifilter->ist->st->codecpar->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        need_reinit |= ifilter->sample_rate    != frame->sample_rate ||
                       ifilter->channels       != frame->channels ||
                       ifilter->channel_layout != frame->channel_layout;
        break;
    case AVMEDIA_TYPE_VIDEO:
        need_reinit |= ifilter->width  != frame->width ||
                       ifilter->height != frame->height;
        break;
    }

    if (!ifilter->ist->reinit_filters && fg->graph)
        need_reinit = 0;

    if (!!ifilter->hw_frames_ctx != !!frame->hw_frames_ctx ||
        (ifilter->hw_frames_ctx && ifilter->hw_frames_ctx->data != frame->hw_frames_ctx->data))
        need_reinit = 1;

    if (need_reinit) {
        ret = ifilter_parameters_from_frame(ifilter, frame);
        if (ret < 0)
            return ret;
    }

    /* (re)init the graph if possible, otherwise buffer the frame and return */
    if (need_reinit || !fg->graph) {
        for (i = 0; i < fg->nb_inputs; i++) {
            if (!ifilter_has_all_input_formats(fg)) {
                AVFrame *tmp = av_frame_clone(frame);
                if (!tmp)
                    return AVERROR(ENOMEM);
                av_frame_unref(frame);

                if (!av_fifo_space(ifilter->frame_queue)) {
                    ret = av_fifo_realloc2(ifilter->frame_queue, 2 * av_fifo_size(ifilter->frame_queue));
                    if (ret < 0) {
                        av_frame_free(&tmp);
                        return ret;
                    }
                }
                av_fifo_generic_write(ifilter->frame_queue, &tmp, sizeof(tmp), NULL);
                return 0;
            }
        }

        ret = reap_filters(1);
        if (ret < 0 && ret != AVERROR_EOF) {
            av_log(NULL, AV_LOG_ERROR, "Error while filtering: %s\n", av_err2str(ret));
            return ret;
        }

        ret = configure_filtergraph(fg);
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "Error reinitializing filters!\n");
            return ret;
        }
    }

    ret = av_buffersrc_add_frame_flags(ifilter->filter, frame, AV_BUFFERSRC_FLAG_PUSH);
    if (ret < 0) {
        if (ret != AVERROR_EOF)
            av_log(NULL, AV_LOG_ERROR, "Error while filtering: %s\n", av_err2str(ret));
        return ret;
    }

    return 0;
}