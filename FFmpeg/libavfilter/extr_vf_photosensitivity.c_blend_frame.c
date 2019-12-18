#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_11__ {scalar_t__ s_mul; int /*<<< orphan*/ * source; int /*<<< orphan*/ * target; } ;
typedef  TYPE_3__ ThreadData_blend_frame ;
struct TYPE_12__ {TYPE_1__** outputs; TYPE_2__* internal; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* execute ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  h; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blend_frame_partial ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blend_frame(AVFilterContext *ctx, AVFrame *target, AVFrame *source, float factor)
{
    ThreadData_blend_frame td;
    td.target = target;
    td.source = source;
    td.s_mul = (uint16_t)(factor * 0x100);
    ctx->internal->execute(ctx, blend_frame_partial, &td, NULL, FFMIN(ctx->outputs[0]->h, ff_filter_get_nb_threads(ctx)));
}