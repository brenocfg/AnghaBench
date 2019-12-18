#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  void* gcov_type ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_11__ {void* count; } ;
struct TYPE_10__ {int probability; void* count; int /*<<< orphan*/  flags; TYPE_2__* dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EDGE_FALSE_VALUE ; 
 int /*<<< orphan*/  EDGE_TRUE_VALUE ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NE_EXPR ; 
 void* REG_BR_PROB_BASE ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_2__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  bsi_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_artificial_label () ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* make_edge (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_edge (TYPE_1__*) ; 
 TYPE_1__* split_block (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
tree_divmod_fixed_value (tree stmt, tree operation, 
			 tree op1, tree op2, tree value, int prob, gcov_type count,
			 gcov_type all)
{
  tree stmt1, stmt2, stmt3;
  tree tmp1, tmp2, tmpv;
  tree label_decl1 = create_artificial_label ();
  tree label_decl2 = create_artificial_label ();
  tree label_decl3 = create_artificial_label ();
  tree label1, label2, label3;
  tree bb1end, bb2end, bb3end;
  basic_block bb, bb2, bb3, bb4;
  tree optype = TREE_TYPE (operation);
  edge e12, e13, e23, e24, e34;
  block_stmt_iterator bsi;

  bb = bb_for_stmt (stmt);
  bsi = bsi_for_stmt (stmt);

  tmpv = create_tmp_var (optype, "PROF");
  tmp1 = create_tmp_var (optype, "PROF");
  stmt1 = build2 (MODIFY_EXPR, optype, tmpv, fold_convert (optype, value));
  stmt2 = build2 (MODIFY_EXPR, optype, tmp1, op2);
  stmt3 = build3 (COND_EXPR, void_type_node,
	    build2 (NE_EXPR, boolean_type_node, tmp1, tmpv),
	    build1 (GOTO_EXPR, void_type_node, label_decl2),
	    build1 (GOTO_EXPR, void_type_node, label_decl1));
  bsi_insert_before (&bsi, stmt1, BSI_SAME_STMT);
  bsi_insert_before (&bsi, stmt2, BSI_SAME_STMT);
  bsi_insert_before (&bsi, stmt3, BSI_SAME_STMT);
  bb1end = stmt3;

  tmp2 = create_tmp_var (optype, "PROF");
  label1 = build1 (LABEL_EXPR, void_type_node, label_decl1);
  stmt1 = build2 (MODIFY_EXPR, optype, tmp2,
		  build2 (TREE_CODE (operation), optype, op1, tmpv));
  bsi_insert_before (&bsi, label1, BSI_SAME_STMT);
  bsi_insert_before (&bsi, stmt1, BSI_SAME_STMT);
  bb2end = stmt1;

  label2 = build1 (LABEL_EXPR, void_type_node, label_decl2);
  stmt1 = build2 (MODIFY_EXPR, optype, tmp2,
		  build2 (TREE_CODE (operation), optype, op1, op2));
  bsi_insert_before (&bsi, label2, BSI_SAME_STMT);
  bsi_insert_before (&bsi, stmt1, BSI_SAME_STMT);
  bb3end = stmt1;

  label3 = build1 (LABEL_EXPR, void_type_node, label_decl3);
  bsi_insert_before (&bsi, label3, BSI_SAME_STMT);

  /* Fix CFG. */
  /* Edge e23 connects bb2 to bb3, etc. */
  e12 = split_block (bb, bb1end);
  bb2 = e12->dest;
  bb2->count = count;
  e23 = split_block (bb2, bb2end);
  bb3 = e23->dest;
  bb3->count = all - count;
  e34 = split_block (bb3, bb3end);
  bb4 = e34->dest;
  bb4->count = all;

  e12->flags &= ~EDGE_FALLTHRU;
  e12->flags |= EDGE_FALSE_VALUE;
  e12->probability = prob;
  e12->count = count;

  e13 = make_edge (bb, bb3, EDGE_TRUE_VALUE);
  e13->probability = REG_BR_PROB_BASE - prob;
  e13->count = all - count;

  remove_edge (e23);
  
  e24 = make_edge (bb2, bb4, EDGE_FALLTHRU);
  e24->probability = REG_BR_PROB_BASE;
  e24->count = count;

  e34->probability = REG_BR_PROB_BASE;
  e34->count = all - count;

  return tmp2;
}