#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  current_bind_expr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 TYPE_1__* gimplify_ctxp ; 

__attribute__((used)) static void
gimple_pop_bind_expr (void)
{
  gimplify_ctxp->current_bind_expr
    = TREE_CHAIN (gimplify_ctxp->current_bind_expr);
}