#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int channels; int planes; int* var_values; int /*<<< orphan*/  sample_fmt; } ;
typedef  TYPE_1__ VolumeContext ;
struct TYPE_9__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_8__ {int channels; int sample_rate; TYPE_3__* src; int /*<<< orphan*/  time_base; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int NAN ; 
 size_t VAR_N ; 
 size_t VAR_NB_CHANNELS ; 
 size_t VAR_NB_CONSUMED_SAMPLES ; 
 size_t VAR_NB_SAMPLES ; 
 size_t VAR_POS ; 
 size_t VAR_PTS ; 
 size_t VAR_SAMPLE_RATE ; 
 size_t VAR_STARTPTS ; 
 size_t VAR_STARTT ; 
 size_t VAR_T ; 
 size_t VAR_TB ; 
 size_t VAR_VOLUME ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 scalar_t__ av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int set_volume (TYPE_3__*) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    VolumeContext *vol   = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];

    vol->sample_fmt = inlink->format;
    vol->channels   = inlink->channels;
    vol->planes     = av_sample_fmt_is_planar(inlink->format) ? vol->channels : 1;

    vol->var_values[VAR_N] =
    vol->var_values[VAR_NB_CONSUMED_SAMPLES] =
    vol->var_values[VAR_NB_SAMPLES] =
    vol->var_values[VAR_POS] =
    vol->var_values[VAR_PTS] =
    vol->var_values[VAR_STARTPTS] =
    vol->var_values[VAR_STARTT] =
    vol->var_values[VAR_T] =
    vol->var_values[VAR_VOLUME] = NAN;

    vol->var_values[VAR_NB_CHANNELS] = inlink->channels;
    vol->var_values[VAR_TB]          = av_q2d(inlink->time_base);
    vol->var_values[VAR_SAMPLE_RATE] = inlink->sample_rate;

    av_log(inlink->src, AV_LOG_VERBOSE, "tb:%f sample_rate:%f nb_channels:%f\n",
           vol->var_values[VAR_TB],
           vol->var_values[VAR_SAMPLE_RATE],
           vol->var_values[VAR_NB_CHANNELS]);

    return set_volume(ctx);
}