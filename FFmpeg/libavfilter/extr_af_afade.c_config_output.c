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
struct TYPE_6__ {int format; int /*<<< orphan*/  sample_rate; TYPE_3__* src; } ;
struct TYPE_5__ {scalar_t__ start_time; void* start_sample; scalar_t__ duration; void* nb_samples; int /*<<< orphan*/  fade_samples; } ;
typedef  TYPE_1__ AudioFadeContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBL 135 
#define  AV_SAMPLE_FMT_DBLP 134 
#define  AV_SAMPLE_FMT_FLT 133 
#define  AV_SAMPLE_FMT_FLTP 132 
#define  AV_SAMPLE_FMT_S16 131 
#define  AV_SAMPLE_FMT_S16P 130 
#define  AV_SAMPLE_FMT_S32 129 
#define  AV_SAMPLE_FMT_S32P 128 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 void* av_rescale (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fade_samples_dbl ; 
 int /*<<< orphan*/  fade_samples_dblp ; 
 int /*<<< orphan*/  fade_samples_flt ; 
 int /*<<< orphan*/  fade_samples_fltp ; 
 int /*<<< orphan*/  fade_samples_s16 ; 
 int /*<<< orphan*/  fade_samples_s16p ; 
 int /*<<< orphan*/  fade_samples_s32 ; 
 int /*<<< orphan*/  fade_samples_s32p ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    AudioFadeContext *s  = ctx->priv;

    switch (outlink->format) {
    case AV_SAMPLE_FMT_DBL:  s->fade_samples = fade_samples_dbl;  break;
    case AV_SAMPLE_FMT_DBLP: s->fade_samples = fade_samples_dblp; break;
    case AV_SAMPLE_FMT_FLT:  s->fade_samples = fade_samples_flt;  break;
    case AV_SAMPLE_FMT_FLTP: s->fade_samples = fade_samples_fltp; break;
    case AV_SAMPLE_FMT_S16:  s->fade_samples = fade_samples_s16;  break;
    case AV_SAMPLE_FMT_S16P: s->fade_samples = fade_samples_s16p; break;
    case AV_SAMPLE_FMT_S32:  s->fade_samples = fade_samples_s32;  break;
    case AV_SAMPLE_FMT_S32P: s->fade_samples = fade_samples_s32p; break;
    }

    if (s->duration)
        s->nb_samples = av_rescale(s->duration, outlink->sample_rate, AV_TIME_BASE);
    if (s->start_time)
        s->start_sample = av_rescale(s->start_time, outlink->sample_rate, AV_TIME_BASE);

    return 0;
}