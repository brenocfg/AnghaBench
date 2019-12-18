#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct omp_region {TYPE_1__* inner; } ;
typedef  TYPE_2__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_6__ {int /*<<< orphan*/  dest; int /*<<< orphan*/  src; } ;
struct TYPE_5__ {int type; int sched_kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_CONTINUE_LINKING ; 
 size_t BUILT_IN_GOMP_PARALLEL_END ; 
 int BUILT_IN_GOMP_PARALLEL_LOOP_STATIC_START ; 
 int BUILT_IN_GOMP_PARALLEL_SECTIONS_START ; 
 int BUILT_IN_GOMP_PARALLEL_START ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EDGE_FALSE_VALUE ; 
 int /*<<< orphan*/  EDGE_TRUE_VALUE ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 int /*<<< orphan*/  OMP_CLAUSE_IF ; 
 int /*<<< orphan*/ * OMP_CLAUSE_IF_EXPR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMP_CLAUSE_NUM_THREADS ; 
 int /*<<< orphan*/ * OMP_CLAUSE_NUM_THREADS_EXPR (int /*<<< orphan*/ *) ; 
#define  OMP_FOR 129 
 int /*<<< orphan*/ * OMP_PARALLEL_CLAUSES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OMP_PARALLEL_DATA_ARG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OMP_PARALLEL_FN (int /*<<< orphan*/ *) ; 
#define  OMP_SECTIONS 128 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_and_jump (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * build_fold_addr_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_function_call_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** built_in_decls ; 
 int /*<<< orphan*/ * chainon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_artificial_label () ; 
 int /*<<< orphan*/  create_empty_bb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_tmp_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_omp_clause (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * get_formal_tmp_var (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * gimple_boolify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ *) ; 
 scalar_t__ is_combined_parallel (struct omp_region*) ; 
 int /*<<< orphan*/  make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * null_pointer_node ; 
 int /*<<< orphan*/  pop_gimplify_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_gimplify_context () ; 
 int /*<<< orphan*/  remove_edge (TYPE_2__*) ; 
 TYPE_2__* split_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unsigned_type_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
expand_parallel_call (struct omp_region *region, basic_block bb,
		      tree entry_stmt, tree ws_args)
{
  tree t, args, val, cond, c, list, clauses;
  block_stmt_iterator si;
  int start_ix;

  clauses = OMP_PARALLEL_CLAUSES (entry_stmt);
  push_gimplify_context ();

  /* Determine what flavor of GOMP_parallel_start we will be
     emitting.  */
  start_ix = BUILT_IN_GOMP_PARALLEL_START;
  if (is_combined_parallel (region))
    {
      switch (region->inner->type)
	{
	case OMP_FOR:
	  start_ix = BUILT_IN_GOMP_PARALLEL_LOOP_STATIC_START
		     + region->inner->sched_kind;
	  break;
	case OMP_SECTIONS:
	  start_ix = BUILT_IN_GOMP_PARALLEL_SECTIONS_START;
	  break;
	default:
	  gcc_unreachable ();
	}
    }

  /* By default, the value of NUM_THREADS is zero (selected at run time)
     and there is no conditional.  */
  cond = NULL_TREE;
  val = build_int_cst (unsigned_type_node, 0);

  c = find_omp_clause (clauses, OMP_CLAUSE_IF);
  if (c)
    cond = OMP_CLAUSE_IF_EXPR (c);

  c = find_omp_clause (clauses, OMP_CLAUSE_NUM_THREADS);
  if (c)
    val = OMP_CLAUSE_NUM_THREADS_EXPR (c);

  /* Ensure 'val' is of the correct type.  */
  val = fold_convert (unsigned_type_node, val);

  /* If we found the clause 'if (cond)', build either
     (cond != 0) or (cond ? val : 1u).  */
  if (cond)
    {
      block_stmt_iterator si;

      cond = gimple_boolify (cond);

      if (integer_zerop (val))
	val = build2 (EQ_EXPR, unsigned_type_node, cond,
		      build_int_cst (TREE_TYPE (cond), 0));
      else
	{
	  basic_block cond_bb, then_bb, else_bb;
	  edge e;
	  tree t, then_lab, else_lab, tmp;

	  tmp = create_tmp_var (TREE_TYPE (val), NULL);
	  e = split_block (bb, NULL);
	  cond_bb = e->src;
	  bb = e->dest;
	  remove_edge (e);

	  then_bb = create_empty_bb (cond_bb);
	  else_bb = create_empty_bb (then_bb);
	  then_lab = create_artificial_label ();
	  else_lab = create_artificial_label ();

	  t = build3 (COND_EXPR, void_type_node,
		      cond,
		      build_and_jump (&then_lab),
		      build_and_jump (&else_lab));

	  si = bsi_start (cond_bb);
	  bsi_insert_after (&si, t, BSI_CONTINUE_LINKING);

	  si = bsi_start (then_bb);
	  t = build1 (LABEL_EXPR, void_type_node, then_lab);
	  bsi_insert_after (&si, t, BSI_CONTINUE_LINKING);
	  t = build2 (MODIFY_EXPR, void_type_node, tmp, val);
	  bsi_insert_after (&si, t, BSI_CONTINUE_LINKING);

	  si = bsi_start (else_bb);
	  t = build1 (LABEL_EXPR, void_type_node, else_lab);
	  bsi_insert_after (&si, t, BSI_CONTINUE_LINKING);
	  t = build2 (MODIFY_EXPR, void_type_node, tmp, 
	              build_int_cst (unsigned_type_node, 1));
	  bsi_insert_after (&si, t, BSI_CONTINUE_LINKING);

	  make_edge (cond_bb, then_bb, EDGE_TRUE_VALUE);
	  make_edge (cond_bb, else_bb, EDGE_FALSE_VALUE);
	  make_edge (then_bb, bb, EDGE_FALLTHRU);
	  make_edge (else_bb, bb, EDGE_FALLTHRU);

	  val = tmp;
	}

      list = NULL_TREE;
      val = get_formal_tmp_var (val, &list);
      si = bsi_start (bb);
      bsi_insert_after (&si, list, BSI_CONTINUE_LINKING);
    }

  list = NULL_TREE;
  args = tree_cons (NULL, val, NULL);
  t = OMP_PARALLEL_DATA_ARG (entry_stmt);
  if (t == NULL)
    t = null_pointer_node;
  else
    t = build_fold_addr_expr (t);
  args = tree_cons (NULL, t, args);
  t = build_fold_addr_expr (OMP_PARALLEL_FN (entry_stmt));
  args = tree_cons (NULL, t, args);

  if (ws_args)
    args = chainon (args, ws_args);

  t = built_in_decls[start_ix];
  t = build_function_call_expr (t, args);
  gimplify_and_add (t, &list);

  t = OMP_PARALLEL_DATA_ARG (entry_stmt);
  if (t == NULL)
    t = null_pointer_node;
  else
    t = build_fold_addr_expr (t);
  args = tree_cons (NULL, t, NULL);
  t = build_function_call_expr (OMP_PARALLEL_FN (entry_stmt), args);
  gimplify_and_add (t, &list);

  t = built_in_decls[BUILT_IN_GOMP_PARALLEL_END];
  t = build_function_call_expr (t, NULL);
  gimplify_and_add (t, &list);

  si = bsi_last (bb);
  bsi_insert_after (&si, list, BSI_CONTINUE_LINKING);

  pop_gimplify_context (NULL_TREE);
}