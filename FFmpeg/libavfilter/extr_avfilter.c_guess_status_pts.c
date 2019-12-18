#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {unsigned int nb_inputs; TYPE_1__** inputs; } ;
struct TYPE_5__ {int status_out; int /*<<< orphan*/  time_base; int /*<<< orphan*/  status_in_pts; int /*<<< orphan*/  current_pts; } ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ FFMIN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t guess_status_pts(AVFilterContext *ctx, int status, AVRational link_time_base)
{
    unsigned i;
    int64_t r = INT64_MAX;

    for (i = 0; i < ctx->nb_inputs; i++)
        if (ctx->inputs[i]->status_out == status)
            r = FFMIN(r, av_rescale_q(ctx->inputs[i]->current_pts, ctx->inputs[i]->time_base, link_time_base));
    if (r < INT64_MAX)
        return r;
    av_log(ctx, AV_LOG_WARNING, "EOF timestamp not reliable\n");
    for (i = 0; i < ctx->nb_inputs; i++)
        r = FFMIN(r, av_rescale_q(ctx->inputs[i]->status_in_pts, ctx->inputs[i]->time_base, link_time_base));
    if (r < INT64_MAX)
        return r;
    return AV_NOPTS_VALUE;
}