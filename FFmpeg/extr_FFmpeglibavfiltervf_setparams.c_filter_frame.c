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
struct TYPE_11__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_10__ {TYPE_4__* dst; } ;
struct TYPE_9__ {int interlaced_frame; scalar_t__ top_field_first; scalar_t__ color_range; scalar_t__ color_primaries; scalar_t__ color_trc; scalar_t__ colorspace; } ;
struct TYPE_8__ {scalar_t__ field_mode; scalar_t__ color_range; scalar_t__ color_primaries; scalar_t__ color_trc; scalar_t__ colorspace; } ;
typedef  TYPE_1__ SetParamsContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ MODE_AUTO ; 
 scalar_t__ MODE_PROG ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    SetParamsContext *s = ctx->priv;

    /* set field */
    if (s->field_mode == MODE_PROG) {
        frame->interlaced_frame = 0;
    } else if (s->field_mode != MODE_AUTO) {
        frame->interlaced_frame = 1;
        frame->top_field_first = s->field_mode;
    }

    /* set range */
    if (s->color_range >= 0)
        frame->color_range = s->color_range;

    /* set color prim, trc, space */
    if (s->color_primaries >= 0)
        frame->color_primaries = s->color_primaries;
    if (s->color_trc >= 0)
        frame->color_trc = s->color_trc;
    if (s->colorspace >= 0)
        frame->colorspace = s->colorspace;
    return ff_filter_frame(ctx->outputs[0], frame);
}