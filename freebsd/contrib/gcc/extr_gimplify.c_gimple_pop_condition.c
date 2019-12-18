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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int conditions; int /*<<< orphan*/  conditional_cleanups; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* gimplify_ctxp ; 

__attribute__((used)) static void
gimple_pop_condition (tree *pre_p)
{
  int conds = --(gimplify_ctxp->conditions);

  gcc_assert (conds >= 0);
  if (conds == 0)
    {
      append_to_statement_list (gimplify_ctxp->conditional_cleanups, pre_p);
      gimplify_ctxp->conditional_cleanups = NULL_TREE;
    }
}