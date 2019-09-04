#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  channels; TYPE_4__* src; } ;
struct TYPE_10__ {scalar_t__ nb_samples; int /*<<< orphan*/  pts; int /*<<< orphan*/  format; int /*<<< orphan*/  extended_data; } ;
struct TYPE_9__ {scalar_t__ remaining; scalar_t__ frame_nsamples_max; int /*<<< orphan*/  next_pts; } ;
typedef  TYPE_1__ FIREqualizerContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  av_samples_set_silence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    FIREqualizerContext *s= ctx->priv;
    int ret;

    ret = ff_request_frame(ctx->inputs[0]);
    if (ret == AVERROR_EOF && s->remaining > 0 && s->frame_nsamples_max > 0) {
        AVFrame *frame = ff_get_audio_buffer(outlink, FFMIN(s->remaining, s->frame_nsamples_max));

        if (!frame)
            return AVERROR(ENOMEM);

        av_samples_set_silence(frame->extended_data, 0, frame->nb_samples, outlink->channels, frame->format);
        frame->pts = s->next_pts;
        s->remaining -= frame->nb_samples;
        ret = filter_frame(ctx->inputs[0], frame);
    }

    return ret;
}