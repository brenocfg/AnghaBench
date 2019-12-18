#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  var; } ;
struct TYPE_6__ {double const* const_values; void* opaque; int /*<<< orphan*/  var; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Parser ;
typedef  TYPE_2__ AVExpr ;

/* Variables and functions */
 double eval_expr (TYPE_1__*,TYPE_2__*) ; 

double av_expr_eval(AVExpr *e, const double *const_values, void *opaque)
{
    Parser p = { 0 };
    p.var= e->var;

    p.const_values = const_values;
    p.opaque     = opaque;
    return eval_expr(&p, e);
}