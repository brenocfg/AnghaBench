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
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ prev_pts; scalar_t__ delta; int /*<<< orphan*/  cfr; int /*<<< orphan*/  avg_delta; scalar_t__ max_delta; scalar_t__ min_delta; int /*<<< orphan*/  vfr; } ;
typedef  TYPE_1__ VFRDETContext ;
struct TYPE_11__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_10__ {TYPE_4__* dst; } ;
struct TYPE_9__ {scalar_t__ pts; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ FFMAX (scalar_t__,scalar_t__) ; 
 scalar_t__ FFMIN (scalar_t__,scalar_t__) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    VFRDETContext *s = ctx->priv;

    if (s->prev_pts != AV_NOPTS_VALUE) {
        int64_t delta = in->pts - s->prev_pts;

        if (s->delta == AV_NOPTS_VALUE) {
            s->delta = delta;
            s->min_delta = delta;
            s->max_delta = delta;
        }

        if (s->delta != delta) {
            s->vfr++;
            s->delta = delta;
            s->min_delta = FFMIN(delta, s->min_delta);
            s->max_delta = FFMAX(delta, s->max_delta);
            s->avg_delta += delta;
        } else {
            s->cfr++;
        }
    }

    s->prev_pts = in->pts;

    return ff_filter_frame(ctx->outputs[0], in);
}