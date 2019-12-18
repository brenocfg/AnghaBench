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
typedef  int /*<<< orphan*/ * tree ;
struct leh_state {TYPE_1__* tf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * try_finally_expr; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_finally_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unsave_expr_now (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
lower_try_finally_dup_block (tree t, struct leh_state *outer_state)
{
  tree region = NULL;

  t = unsave_expr_now (t);

  if (outer_state->tf)
    region = outer_state->tf->try_finally_expr;
  collect_finally_tree (t, region);

  return t;
}