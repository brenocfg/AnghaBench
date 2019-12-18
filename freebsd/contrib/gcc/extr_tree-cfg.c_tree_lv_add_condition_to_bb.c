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
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_NEW_STMT ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EDGE_FALSE_VALUE ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* single_succ_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_block_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
tree_lv_add_condition_to_bb (basic_block first_head, basic_block second_head,
                            basic_block cond_bb, void *cond_e)
{
  block_stmt_iterator bsi;
  tree goto1 = NULL_TREE;
  tree goto2 = NULL_TREE;
  tree new_cond_expr = NULL_TREE;
  tree cond_expr = (tree) cond_e;
  edge e0;

  /* Build new conditional expr */
  goto1 = build1 (GOTO_EXPR, void_type_node, tree_block_label (first_head));
  goto2 = build1 (GOTO_EXPR, void_type_node, tree_block_label (second_head));
  new_cond_expr = build3 (COND_EXPR, void_type_node, cond_expr, goto1, goto2);

  /* Add new cond in cond_bb.  */
  bsi = bsi_start (cond_bb);
  bsi_insert_after (&bsi, new_cond_expr, BSI_NEW_STMT);
  /* Adjust edges appropriately to connect new head with first head
     as well as second head.  */
  e0 = single_succ_edge (cond_bb);
  e0->flags &= ~EDGE_FALLTHRU;
  e0->flags |= EDGE_FALSE_VALUE;
}