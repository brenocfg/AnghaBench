#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {scalar_t__ latch; } ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/ * basic_block ;
struct TYPE_3__ {scalar_t__ dest; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 TYPE_1__* EDGE_SUCC (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ flow_bb_inside_loop_p (struct loop*,scalar_t__) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * single_pred (scalar_t__) ; 
 int /*<<< orphan*/  single_pred_p (scalar_t__) ; 

basic_block
ip_normal_pos (struct loop *loop)
{
  tree last;
  basic_block bb;
  edge exit;

  if (!single_pred_p (loop->latch))
    return NULL;

  bb = single_pred (loop->latch);
  last = last_stmt (bb);
  if (TREE_CODE (last) != COND_EXPR)
    return NULL;

  exit = EDGE_SUCC (bb, 0);
  if (exit->dest == loop->latch)
    exit = EDGE_SUCC (bb, 1);

  if (flow_bb_inside_loop_p (loop, exit->dest))
    return NULL;

  return bb;
}