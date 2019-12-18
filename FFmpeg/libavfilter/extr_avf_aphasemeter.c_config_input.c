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
struct TYPE_8__ {int partial_buf_size; int min_samples; int max_samples; int /*<<< orphan*/  sample_rate; TYPE_4__* dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_7__ {TYPE_1__ frame_rate; scalar_t__ do_video; } ;
typedef  TYPE_2__ AudioPhaseMeterContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioPhaseMeterContext *s = ctx->priv;
    int nb_samples;

    if (s->do_video) {
        nb_samples = FFMAX(1, av_rescale(inlink->sample_rate, s->frame_rate.den, s->frame_rate.num));
        inlink->partial_buf_size =
        inlink->min_samples =
        inlink->max_samples = nb_samples;
    }

    return 0;
}