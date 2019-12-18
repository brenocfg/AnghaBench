#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* internal; TYPE_2__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_15__ {scalar_t__ nb_samples; scalar_t__ extended_data; scalar_t__ pts; } ;
struct TYPE_14__ {scalar_t__ win_size; int /*<<< orphan*/  fifo; scalar_t__ hop_size; scalar_t__ consumed; scalar_t__ pts; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* execute ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_2__ ShowSpatialContext ;
typedef  TYPE_3__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_audio_fifo_drain (int /*<<< orphan*/ ,scalar_t__) ; 
 int av_audio_fifo_peek (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_audio_fifo_write (int /*<<< orphan*/ ,void**,scalar_t__) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int draw_spatial (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_4__*,int) ; 
 TYPE_3__* ff_get_audio_buffer (int /*<<< orphan*/ *,scalar_t__) ; 
 int ff_inlink_consume_frame (int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_outlink_frame_wanted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_channel_fft ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int spatial_activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    ShowSpatialContext *s = ctx->priv;
    int ret;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (av_audio_fifo_size(s->fifo) < s->win_size) {
        AVFrame *frame = NULL;

        ret = ff_inlink_consume_frame(inlink, &frame);
        if (ret < 0)
            return ret;
        if (ret > 0) {
            s->pts = frame->pts;
            s->consumed = 0;

            av_audio_fifo_write(s->fifo, (void **)frame->extended_data, frame->nb_samples);
            av_frame_free(&frame);
        }
    }

    if (av_audio_fifo_size(s->fifo) >= s->win_size) {
        AVFrame *fin = ff_get_audio_buffer(inlink, s->win_size);
        if (!fin)
            return AVERROR(ENOMEM);

        fin->pts = s->pts + s->consumed;
        s->consumed += s->hop_size;
        ret = av_audio_fifo_peek(s->fifo, (void **)fin->extended_data,
                                 FFMIN(s->win_size, av_audio_fifo_size(s->fifo)));
        if (ret < 0) {
            av_frame_free(&fin);
            return ret;
        }

        av_assert0(fin->nb_samples == s->win_size);

        ctx->internal->execute(ctx, run_channel_fft, fin, NULL, 2);

        ret = draw_spatial(inlink, fin);

        av_frame_free(&fin);
        av_audio_fifo_drain(s->fifo, s->hop_size);
        if (ret <= 0)
            return ret;
    }

    FF_FILTER_FORWARD_STATUS(inlink, outlink);
    if (ff_outlink_frame_wanted(outlink) && av_audio_fifo_size(s->fifo) < s->win_size) {
        ff_inlink_request_frame(inlink);
        return 0;
    }

    if (av_audio_fifo_size(s->fifo) >= s->win_size) {
        ff_filter_set_ready(ctx, 10);
        return 0;
    }
    return FFERROR_NOT_READY;
}