#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int64_t ;
struct TYPE_17__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_16__ {TYPE_4__* dst; } ;
struct TYPE_15__ {int /*<<< orphan*/  nb_samples; scalar_t__* data; } ;
struct TYPE_14__ {int /*<<< orphan*/ * histogram; int /*<<< orphan*/  peak; } ;
typedef  TYPE_1__ ReplayGainContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ HISTOGRAM_SLOTS ; 
 size_t av_clip64 (size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  butter_filter_stereo_samples (TYPE_1__*,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_stereo_peak (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int calc_stereo_rms (float*,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floor (int) ; 
 size_t lrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yule_filter_stereo_samples (TYPE_1__*,float const*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    ReplayGainContext *s = ctx->priv;
    int64_t level;
    AVFrame *out;

    out = ff_get_audio_buffer(outlink, in->nb_samples);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    calc_stereo_peak((float *)in->data[0],
                              in->nb_samples, &s->peak);
    yule_filter_stereo_samples(s, (const float *)in->data[0],
                                        (float *)out->data[0],
                                                 out->nb_samples);
    butter_filter_stereo_samples(s, (float *)out->data[0],
                                             out->nb_samples);
    level = lrint(floor(100 * calc_stereo_rms((float *)out->data[0],
                                                           out->nb_samples)));
    level = av_clip64(level, 0, HISTOGRAM_SLOTS - 1);

    s->histogram[level]++;

    av_frame_free(&out);
    return ff_filter_frame(outlink, in);
}