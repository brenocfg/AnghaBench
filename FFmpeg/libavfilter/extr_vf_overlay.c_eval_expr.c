#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsub; void** var_values; void* y; int /*<<< orphan*/  hsub; void* x; int /*<<< orphan*/  x_pexpr; int /*<<< orphan*/  y_pexpr; } ;
typedef  TYPE_1__ OverlayContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 size_t VAR_X ; 
 size_t VAR_Y ; 
 void* av_expr_eval (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 void* normalize_xy (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eval_expr(AVFilterContext *ctx)
{
    OverlayContext *s = ctx->priv;

    s->var_values[VAR_X] = av_expr_eval(s->x_pexpr, s->var_values, NULL);
    s->var_values[VAR_Y] = av_expr_eval(s->y_pexpr, s->var_values, NULL);
    /* It is necessary if x is expressed from y  */
    s->var_values[VAR_X] = av_expr_eval(s->x_pexpr, s->var_values, NULL);
    s->x = normalize_xy(s->var_values[VAR_X], s->hsub);
    s->y = normalize_xy(s->var_values[VAR_Y], s->vsub);
}