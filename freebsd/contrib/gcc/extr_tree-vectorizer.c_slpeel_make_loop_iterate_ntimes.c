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
struct loop {int /*<<< orphan*/  nb_iterations; TYPE_1__* single_exit; int /*<<< orphan*/  latch; } ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  dest; } ;
typedef  scalar_t__ LOC ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int EDGE_TRUE_VALUE ; 
 int /*<<< orphan*/  GE_EXPR ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 char* LOC_FILE (scalar_t__) ; 
 int LOC_LINE (scalar_t__) ; 
 int /*<<< orphan*/  LT_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNKNOWN_LOC ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  bsi_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct loop*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ find_loop_location (struct loop*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_loop_exit_condition (struct loop*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_iv_increment_position (struct loop*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  tree_block_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

void
slpeel_make_loop_iterate_ntimes (struct loop *loop, tree niters)
{
  tree indx_before_incr, indx_after_incr, cond_stmt, cond;
  tree orig_cond;
  edge exit_edge = loop->single_exit;
  block_stmt_iterator loop_cond_bsi;
  block_stmt_iterator incr_bsi;
  bool insert_after;
  tree begin_label = tree_block_label (loop->latch);
  tree exit_label = tree_block_label (loop->single_exit->dest);
  tree init = build_int_cst (TREE_TYPE (niters), 0);
  tree step = build_int_cst (TREE_TYPE (niters), 1);
  tree then_label;
  tree else_label;
  LOC loop_loc;

  orig_cond = get_loop_exit_condition (loop);
  gcc_assert (orig_cond);
  loop_cond_bsi = bsi_for_stmt (orig_cond);

  standard_iv_increment_position (loop, &incr_bsi, &insert_after);
  create_iv (init, step, NULL_TREE, loop,
             &incr_bsi, insert_after, &indx_before_incr, &indx_after_incr);

  if (exit_edge->flags & EDGE_TRUE_VALUE) /* 'then' edge exits the loop.  */
    {
      cond = build2 (GE_EXPR, boolean_type_node, indx_after_incr, niters);
      then_label = build1 (GOTO_EXPR, void_type_node, exit_label);
      else_label = build1 (GOTO_EXPR, void_type_node, begin_label);
    }
  else /* 'then' edge loops back.  */
    {
      cond = build2 (LT_EXPR, boolean_type_node, indx_after_incr, niters);
      then_label = build1 (GOTO_EXPR, void_type_node, begin_label);
      else_label = build1 (GOTO_EXPR, void_type_node, exit_label);
    }

  cond_stmt = build3 (COND_EXPR, TREE_TYPE (orig_cond), cond,
		     then_label, else_label);
  bsi_insert_before (&loop_cond_bsi, cond_stmt, BSI_SAME_STMT);

  /* Remove old loop exit test:  */
  bsi_remove (&loop_cond_bsi, true);

  loop_loc = find_loop_location (loop);
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      if (loop_loc != UNKNOWN_LOC)
        fprintf (dump_file, "\nloop at %s:%d: ",
                 LOC_FILE (loop_loc), LOC_LINE (loop_loc));
      print_generic_expr (dump_file, cond_stmt, TDF_SLIM);
    }

  loop->nb_iterations = niters;
}