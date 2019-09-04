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
struct TYPE_6__ {int sample_rate; TYPE_3__* dst; } ;
struct TYPE_5__ {double threshold; int attack; int release; double lin_knee_stop; double lin_knee_start; void* knee_stop; void* knee_start; void* thres; void* release_coeff; void* attack_coeff; scalar_t__ detection; int /*<<< orphan*/  knee; } ;
typedef  TYPE_1__ AudioGateContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 void* FFMIN (int,int) ; 
 void* log (double) ; 
 double sqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int agate_config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioGateContext *s = ctx->priv;
    double lin_threshold = s->threshold;
    double lin_knee_sqrt = sqrt(s->knee);

    if (s->detection)
        lin_threshold *= lin_threshold;

    s->attack_coeff  = FFMIN(1., 1. / (s->attack * inlink->sample_rate / 4000.));
    s->release_coeff = FFMIN(1., 1. / (s->release * inlink->sample_rate / 4000.));
    s->lin_knee_stop = lin_threshold * lin_knee_sqrt;
    s->lin_knee_start = lin_threshold / lin_knee_sqrt;
    s->thres = log(lin_threshold);
    s->knee_start = log(s->lin_knee_start);
    s->knee_stop = log(s->lin_knee_stop);

    return 0;
}