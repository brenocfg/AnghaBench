#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_4__* src; } ;
struct TYPE_12__ {int nb_samples; int /*<<< orphan*/  pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  extended_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  next_pts; scalar_t__ avr; scalar_t__ got_output; } ;
typedef  TYPE_1__ ResampleContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int avresample_convert (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avresample_get_out_samples (scalar_t__,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    ResampleContext   *s = ctx->priv;
    int ret = 0;

    s->got_output = 0;
    while (ret >= 0 && !s->got_output)
        ret = ff_request_frame(ctx->inputs[0]);

    /* flush the lavr delay buffer */
    if (ret == AVERROR_EOF && s->avr) {
        AVFrame *frame;
        int nb_samples = avresample_get_out_samples(s->avr, 0);

        if (!nb_samples)
            return ret;

        frame = ff_get_audio_buffer(outlink, nb_samples);
        if (!frame)
            return AVERROR(ENOMEM);

        ret = avresample_convert(s->avr, frame->extended_data,
                                 frame->linesize[0], nb_samples,
                                 NULL, 0, 0);
        if (ret <= 0) {
            av_frame_free(&frame);
            return (ret == 0) ? AVERROR_EOF : ret;
        }

        frame->nb_samples = ret;
        frame->pts = s->next_pts;
        return ff_filter_frame(outlink, frame);
    }
    return ret;
}