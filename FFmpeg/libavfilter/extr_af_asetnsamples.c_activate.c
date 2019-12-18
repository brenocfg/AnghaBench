#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ nb_out_samples; int /*<<< orphan*/  pad; } ;
struct TYPE_13__ {TYPE_3__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_12__ {scalar_t__ nb_samples; int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  extended_data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;
typedef  TYPE_3__ ASNSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int av_frame_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int /*<<< orphan*/  av_samples_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_samples_set_silence (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_2__*,int) ; 
 TYPE_1__* ff_get_audio_buffer (int /*<<< orphan*/ *,scalar_t__) ; 
 int ff_inlink_consume_samples (int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_1__**) ; 
 scalar_t__ ff_inlink_queued_samples (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    ASNSContext *s = ctx->priv;
    AVFrame *frame = NULL, *pad_frame;
    int ret;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    ret = ff_inlink_consume_samples(inlink, s->nb_out_samples, s->nb_out_samples, &frame);
    if (ret < 0)
        return ret;

    if (ret > 0) {
        if (!s->pad || frame->nb_samples == s->nb_out_samples) {
            ret = ff_filter_frame(outlink, frame);
            if (ff_inlink_queued_samples(inlink) >= s->nb_out_samples)
                ff_filter_set_ready(ctx, 100);
            return ret;
        }

        pad_frame = ff_get_audio_buffer(outlink, s->nb_out_samples);
        if (!pad_frame) {
            av_frame_free(&frame);
            return AVERROR(ENOMEM);
        }

        ret = av_frame_copy_props(pad_frame, frame);
        if (ret < 0) {
            av_frame_free(&pad_frame);
            av_frame_free(&frame);
            return ret;
        }

        av_samples_copy(pad_frame->extended_data, frame->extended_data,
                        0, 0, frame->nb_samples, frame->channels, frame->format);
        av_samples_set_silence(pad_frame->extended_data, frame->nb_samples,
                               s->nb_out_samples - frame->nb_samples, frame->channels,
                               frame->format);
        av_frame_free(&frame);
        return ff_filter_frame(outlink, pad_frame);
    }

    FF_FILTER_FORWARD_STATUS(inlink, outlink);
    FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}