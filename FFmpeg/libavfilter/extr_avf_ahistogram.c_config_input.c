#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int channels; int /*<<< orphan*/  sample_rate; TYPE_4__* dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_7__ {int dchannels; scalar_t__ dmode; void* achistogram; int /*<<< orphan*/  w; void* shistogram; TYPE_1__ frame_rate; int /*<<< orphan*/  nb_samples; } ;
typedef  TYPE_2__ AudioHistogramContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SINGLE ; 
 void* av_calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioHistogramContext *s = ctx->priv;

    s->nb_samples = FFMAX(1, av_rescale(inlink->sample_rate, s->frame_rate.den, s->frame_rate.num));
    s->dchannels = s->dmode == SINGLE ? 1 : inlink->channels;
    s->shistogram = av_calloc(s->w, s->dchannels * sizeof(*s->shistogram));
    if (!s->shistogram)
        return AVERROR(ENOMEM);

    s->achistogram = av_calloc(s->w, s->dchannels * sizeof(*s->achistogram));
    if (!s->achistogram)
        return AVERROR(ENOMEM);

    return 0;
}