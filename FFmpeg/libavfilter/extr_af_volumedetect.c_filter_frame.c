#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_8__ {int /*<<< orphan*/ * histogram; } ;
typedef  TYPE_1__ VolDetectContext ;
struct TYPE_11__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_10__ {TYPE_4__* dst; } ;
struct TYPE_9__ {int nb_samples; int channels; scalar_t__* extended_data; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *samples)
{
    AVFilterContext *ctx = inlink->dst;
    VolDetectContext *vd = ctx->priv;
    int nb_samples  = samples->nb_samples;
    int nb_channels = samples->channels;
    int nb_planes   = nb_channels;
    int plane, i;
    int16_t *pcm;

    if (!av_sample_fmt_is_planar(samples->format)) {
        nb_samples *= nb_channels;
        nb_planes = 1;
    }
    for (plane = 0; plane < nb_planes; plane++) {
        pcm = (int16_t *)samples->extended_data[plane];
        for (i = 0; i < nb_samples; i++)
            vd->histogram[pcm[i] + 0x8000]++;
    }

    return ff_filter_frame(inlink->dst->outputs[0], samples);
}