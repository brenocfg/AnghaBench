#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* var; struct TYPE_4__** param; } ;
typedef  TYPE_1__ AVExpr ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

void av_expr_free(AVExpr *e)
{
    if (!e) return;
    av_expr_free(e->param[0]);
    av_expr_free(e->param[1]);
    av_expr_free(e->param[2]);
    av_freep(&e->var);
    av_freep(&e);
}