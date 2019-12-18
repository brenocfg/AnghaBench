#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  edge_iterator ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_9__ {int /*<<< orphan*/  succs; } ;
struct TYPE_8__ {TYPE_2__* dest; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 scalar_t__ GOTO_EXPR ; 
 scalar_t__ SWITCH_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (TYPE_2__*) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* ei_safe_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_edge (TYPE_1__*) ; 

__attribute__((used)) static void
remove_ctrl_stmt_and_useless_edges (basic_block bb, basic_block dest_bb)
{
  block_stmt_iterator bsi;
  edge e;
  edge_iterator ei;

  bsi = bsi_last (bb);

  /* If the duplicate ends with a control statement, then remove it.

     Note that if we are duplicating the template block rather than the
     original basic block, then the duplicate might not have any real
     statements in it.  */
  if (!bsi_end_p (bsi)
      && bsi_stmt (bsi)
      && (TREE_CODE (bsi_stmt (bsi)) == COND_EXPR
	  || TREE_CODE (bsi_stmt (bsi)) == GOTO_EXPR
	  || TREE_CODE (bsi_stmt (bsi)) == SWITCH_EXPR))
    bsi_remove (&bsi, true);

  for (ei = ei_start (bb->succs); (e = ei_safe_edge (ei)); )
    {
      if (e->dest != dest_bb)
	remove_edge (e);
      else
	ei_next (&ei);
    }
}