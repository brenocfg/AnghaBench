#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  dest; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_NEW_STMT ; 
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EDGE_FALSE_VALUE ; 
 TYPE_1__* EDGE_SUCC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_TRUE_VALUE ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_immediate_dominator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_block_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static edge
slpeel_add_loop_guard (basic_block guard_bb, tree cond, basic_block exit_bb,
		        basic_block dom_bb)
{
  block_stmt_iterator bsi;
  edge new_e, enter_e;
  tree cond_stmt, then_label, else_label;

  enter_e = EDGE_SUCC (guard_bb, 0);
  enter_e->flags &= ~EDGE_FALLTHRU;
  enter_e->flags |= EDGE_FALSE_VALUE;
  bsi = bsi_last (guard_bb);

  then_label = build1 (GOTO_EXPR, void_type_node,
                       tree_block_label (exit_bb));
  else_label = build1 (GOTO_EXPR, void_type_node,
                       tree_block_label (enter_e->dest));
  cond_stmt = build3 (COND_EXPR, void_type_node, cond,
   		     then_label, else_label);
  bsi_insert_after (&bsi, cond_stmt, BSI_NEW_STMT);
  /* Add new edge to connect guard block to the merge/loop-exit block.  */
  new_e = make_edge (guard_bb, exit_bb, EDGE_TRUE_VALUE);
  set_immediate_dominator (CDI_DOMINATORS, exit_bb, dom_bb);
  return new_e;
}