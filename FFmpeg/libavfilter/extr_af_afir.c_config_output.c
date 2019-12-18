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
struct TYPE_9__ {TYPE_1__** inputs; TYPE_2__* priv; } ;
struct TYPE_8__ {int channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  time_base; int /*<<< orphan*/  sample_rate; TYPE_4__* src; } ;
struct TYPE_7__ {int one2many; int nb_channels; int nb_coef_channels; int /*<<< orphan*/  pts; } ;
struct TYPE_6__ {int channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  time_base; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_2__ AudioFIRContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    AudioFIRContext *s = ctx->priv;

    s->one2many = ctx->inputs[1]->channels == 1;
    outlink->sample_rate = ctx->inputs[0]->sample_rate;
    outlink->time_base   = ctx->inputs[0]->time_base;
    outlink->channel_layout = ctx->inputs[0]->channel_layout;
    outlink->channels = ctx->inputs[0]->channels;

    s->nb_channels = outlink->channels;
    s->nb_coef_channels = ctx->inputs[1]->channels;
    s->pts = AV_NOPTS_VALUE;

    return 0;
}