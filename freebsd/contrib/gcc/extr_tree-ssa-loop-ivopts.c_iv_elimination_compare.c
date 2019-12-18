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
struct loop {int dummy; } ;
struct ivopts_data {struct loop* current_loop; } ;
struct iv_use {int /*<<< orphan*/  stmt; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 TYPE_1__* EDGE_SUCC (int /*<<< orphan*/ ,int) ; 
 int EDGE_TRUE_VALUE ; 
 int EQ_EXPR ; 
 int NE_EXPR ; 
 int /*<<< orphan*/  bb_for_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ flow_bb_inside_loop_p (struct loop*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum tree_code
iv_elimination_compare (struct ivopts_data *data, struct iv_use *use)
{
  struct loop *loop = data->current_loop;
  basic_block ex_bb;
  edge exit;

  ex_bb = bb_for_stmt (use->stmt);
  exit = EDGE_SUCC (ex_bb, 0);
  if (flow_bb_inside_loop_p (loop, exit->dest))
    exit = EDGE_SUCC (ex_bb, 1);

  return (exit->flags & EDGE_TRUE_VALUE ? EQ_EXPR : NE_EXPR);
}