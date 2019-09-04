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
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {unsigned int nb_outputs; TYPE_2__* priv; } ;
struct TYPE_6__ {unsigned int cur_idx; int /*<<< orphan*/  delta_ts; TYPE_1__* in; } ;
struct TYPE_5__ {scalar_t__ pts; } ;
typedef  TYPE_2__ ConcatContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ FFMAX (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void find_next_delta_ts(AVFilterContext *ctx, int64_t *seg_delta)
{
    ConcatContext *cat = ctx->priv;
    unsigned i = cat->cur_idx;
    unsigned imax = i + ctx->nb_outputs;
    int64_t pts;

    pts = cat->in[i++].pts;
    for (; i < imax; i++)
        pts = FFMAX(pts, cat->in[i].pts);
    cat->delta_ts += pts;
    *seg_delta = pts;
}