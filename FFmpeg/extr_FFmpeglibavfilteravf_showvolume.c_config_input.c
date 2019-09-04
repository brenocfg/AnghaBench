#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int sample_rate; int partial_buf_size; int min_samples; int max_samples; int channels; TYPE_3__* dst; } ;
struct TYPE_5__ {int w; int rms_factor; int mode; int draw_persistent_duration; int persistent_max_frames; void* nb_frames_max_display; void* max_persistent; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  meter; void* max; void* color_lut; void* values; } ;
typedef  TYPE_1__ ShowVolumeContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int VAR_VARS_NB ; 
 void* av_calloc (int,int) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_peak ; 
 int /*<<< orphan*/  find_rms ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ShowVolumeContext *s = ctx->priv;
    int nb_samples;

    nb_samples = FFMAX(1024, ((double)inlink->sample_rate / av_q2d(s->frame_rate)) + 0.5);
    inlink->partial_buf_size =
    inlink->min_samples =
    inlink->max_samples = nb_samples;
    s->values = av_calloc(inlink->channels * VAR_VARS_NB, sizeof(double));
    if (!s->values)
        return AVERROR(ENOMEM);

    s->color_lut = av_calloc(s->w, sizeof(*s->color_lut) * inlink->channels);
    if (!s->color_lut)
        return AVERROR(ENOMEM);

    s->max = av_calloc(inlink->channels, sizeof(*s->max));
    if (!s->max)
        return AVERROR(ENOMEM);

    s->rms_factor = 10000. / inlink->sample_rate;

    switch (s->mode) {
    case 0: s->meter = find_peak; break;
    case 1: s->meter = find_rms;  break;
    default: return AVERROR_BUG;
    }

    if (s->draw_persistent_duration > 0.) {
        s->persistent_max_frames = (int) FFMAX(av_q2d(s->frame_rate) * s->draw_persistent_duration, 1.);
        s->max_persistent = av_calloc(inlink->channels * s->persistent_max_frames, sizeof(*s->max_persistent));
        s->nb_frames_max_display = av_calloc(inlink->channels * s->persistent_max_frames, sizeof(*s->nb_frames_max_display));
    }
    return 0;
}