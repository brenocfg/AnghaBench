#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* tree ;
struct omp_region {int /*<<< orphan*/  exit; int /*<<< orphan*/  cont; int /*<<< orphan*/  entry; } ;
struct omp_for_data {scalar_t__ cond_code; void* v; void* step; void* n1; void* chunk_size; void* n2; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_CONTINUE_LINKING ; 
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 size_t BUILT_IN_OMP_GET_NUM_THREADS ; 
 size_t BUILT_IN_OMP_GET_THREAD_NUM ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EDGE_FALSE_VALUE ; 
 int /*<<< orphan*/  EDGE_TRUE_VALUE ; 
 scalar_t__ LT_EXPR ; 
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ MIN_EXPR ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ MULT_EXPR ; 
 scalar_t__ OMP_CONTINUE ; 
 scalar_t__ OMP_FOR ; 
 int /*<<< orphan*/  OMP_RETURN_NOWAIT (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 void* TREE_TYPE (void*) ; 
 scalar_t__ TRUNC_DIV_EXPR ; 
 void* alloc_stmt_list () ; 
 int /*<<< orphan*/  append_to_statement_list (void*,void**) ; 
 void* boolean_type_node ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 void* build2 (scalar_t__,void*,void*,void*) ; 
 void* build3 (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_and_jump (void**) ; 
 void* build_function_call_expr (void*,int /*<<< orphan*/ *) ; 
 void* build_int_cst (void*,int) ; 
 int /*<<< orphan*/  build_omp_barrier (void**) ; 
 void** built_in_decls ; 
 int /*<<< orphan*/  create_empty_bb (int /*<<< orphan*/ ) ; 
 void* fold_build2 (scalar_t__,void*,void*,void*) ; 
 void* fold_convert (void*,void*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 void* get_formal_tmp_var (void*,void**) ; 
 void* get_initialized_tmp_var (void*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_and_add (void*,void**) ; 
 scalar_t__ is_gimple_val (void*) ; 
 int /*<<< orphan*/  make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_succ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_succ_edge (int /*<<< orphan*/ ) ; 
 void* tree_block_label (int /*<<< orphan*/ ) ; 
 void* void_type_node ; 

__attribute__((used)) static void
expand_omp_for_static_chunk (struct omp_region *region, struct omp_for_data *fd)
{
  tree l0, l1, l2, l3, l4, n, s0, e0, e, t;
  tree trip, nthreads, threadid;
  tree type;
  basic_block entry_bb, exit_bb, body_bb, seq_start_bb, iter_part_bb;
  basic_block trip_update_bb, cont_bb, fin_bb;
  tree list;
  block_stmt_iterator si;

  type = TREE_TYPE (fd->v);

  entry_bb = region->entry;
  iter_part_bb = create_empty_bb (entry_bb);
  seq_start_bb = create_empty_bb (iter_part_bb);
  body_bb = single_succ (entry_bb);
  cont_bb = region->cont;
  trip_update_bb = create_empty_bb (cont_bb);
  fin_bb = single_succ (cont_bb);
  exit_bb = region->exit;

  l0 = tree_block_label (iter_part_bb);
  l1 = tree_block_label (seq_start_bb);
  l2 = tree_block_label (body_bb);
  l3 = tree_block_label (trip_update_bb);
  l4 = tree_block_label (fin_bb);

  /* Trip and adjustment setup goes in ENTRY_BB.  */
  list = alloc_stmt_list ();

  t = built_in_decls[BUILT_IN_OMP_GET_NUM_THREADS];
  t = build_function_call_expr (t, NULL);
  t = fold_convert (type, t);
  nthreads = get_formal_tmp_var (t, &list);
  
  t = built_in_decls[BUILT_IN_OMP_GET_THREAD_NUM];
  t = build_function_call_expr (t, NULL);
  t = fold_convert (type, t);
  threadid = get_formal_tmp_var (t, &list);

  fd->n1 = fold_convert (type, fd->n1);
  if (!is_gimple_val (fd->n1))
    fd->n1 = get_formal_tmp_var (fd->n1, &list);

  fd->n2 = fold_convert (type, fd->n2);
  if (!is_gimple_val (fd->n2))
    fd->n2 = get_formal_tmp_var (fd->n2, &list);

  fd->step = fold_convert (type, fd->step);
  if (!is_gimple_val (fd->step))
    fd->step = get_formal_tmp_var (fd->step, &list);

  fd->chunk_size = fold_convert (type, fd->chunk_size);
  if (!is_gimple_val (fd->chunk_size))
    fd->chunk_size = get_formal_tmp_var (fd->chunk_size, &list);

  t = build_int_cst (type, (fd->cond_code == LT_EXPR ? -1 : 1));
  t = fold_build2 (PLUS_EXPR, type, fd->step, t);
  t = fold_build2 (PLUS_EXPR, type, t, fd->n2);
  t = fold_build2 (MINUS_EXPR, type, t, fd->n1);
  t = fold_build2 (TRUNC_DIV_EXPR, type, t, fd->step);
  t = fold_convert (type, t);
  if (is_gimple_val (t))
    n = t;
  else
    n = get_formal_tmp_var (t, &list);

  t = build_int_cst (type, 0);
  trip = get_initialized_tmp_var (t, &list, NULL);

  si = bsi_last (entry_bb);
  gcc_assert (TREE_CODE (bsi_stmt (si)) == OMP_FOR);
  bsi_insert_after (&si, list, BSI_SAME_STMT);
  bsi_remove (&si, true);

  /* Iteration space partitioning goes in ITER_PART_BB.  */
  list = alloc_stmt_list ();

  t = build2 (MULT_EXPR, type, trip, nthreads);
  t = build2 (PLUS_EXPR, type, t, threadid);
  t = build2 (MULT_EXPR, type, t, fd->chunk_size);
  s0 = get_formal_tmp_var (t, &list);

  t = build2 (PLUS_EXPR, type, s0, fd->chunk_size);
  t = build2 (MIN_EXPR, type, t, n);
  e0 = get_formal_tmp_var (t, &list);

  t = build2 (LT_EXPR, boolean_type_node, s0, n);
  t = build3 (COND_EXPR, void_type_node, t,
	      build_and_jump (&l1), build_and_jump (&l4));
  append_to_statement_list (t, &list);

  si = bsi_start (iter_part_bb);
  bsi_insert_after (&si, list, BSI_CONTINUE_LINKING);

  /* Setup code for sequential iteration goes in SEQ_START_BB.  */
  list = alloc_stmt_list ();

  t = fold_convert (type, s0);
  t = build2 (MULT_EXPR, type, t, fd->step);
  t = build2 (PLUS_EXPR, type, t, fd->n1);
  t = build2 (MODIFY_EXPR, void_type_node, fd->v, t);
  gimplify_and_add (t, &list);

  t = fold_convert (type, e0);
  t = build2 (MULT_EXPR, type, t, fd->step);
  t = build2 (PLUS_EXPR, type, t, fd->n1);
  e = get_formal_tmp_var (t, &list);

  si = bsi_start (seq_start_bb);
  bsi_insert_after (&si, list, BSI_CONTINUE_LINKING);

  /* The code controlling the sequential loop goes in CONT_BB,
     replacing the OMP_CONTINUE.  */
  list = alloc_stmt_list ();

  t = build2 (PLUS_EXPR, type, fd->v, fd->step);
  t = build2 (MODIFY_EXPR, void_type_node, fd->v, t);
  gimplify_and_add (t, &list);

  t = build2 (fd->cond_code, boolean_type_node, fd->v, e);
  t = get_formal_tmp_var (t, &list);
  t = build3 (COND_EXPR, void_type_node, t,
	      build_and_jump (&l2), build_and_jump (&l3));
  append_to_statement_list (t, &list);
  
  si = bsi_last (cont_bb);
  gcc_assert (TREE_CODE (bsi_stmt (si)) == OMP_CONTINUE);
  bsi_insert_after (&si, list, BSI_SAME_STMT);
  bsi_remove (&si, true);

  /* Trip update code goes into TRIP_UPDATE_BB.  */
  list = alloc_stmt_list ();

  t = build_int_cst (type, 1);
  t = build2 (PLUS_EXPR, type, trip, t);
  t = build2 (MODIFY_EXPR, void_type_node, trip, t);
  gimplify_and_add (t, &list);

  si = bsi_start (trip_update_bb);
  bsi_insert_after (&si, list, BSI_CONTINUE_LINKING);

  /* Replace the OMP_RETURN with a barrier, or nothing.  */
  si = bsi_last (exit_bb);
  if (!OMP_RETURN_NOWAIT (bsi_stmt (si)))
    {
      list = alloc_stmt_list ();
      build_omp_barrier (&list);
      bsi_insert_after (&si, list, BSI_SAME_STMT);
    }
  bsi_remove (&si, true);

  /* Connect the new blocks.  */
  remove_edge (single_succ_edge (entry_bb));
  make_edge (entry_bb, iter_part_bb, EDGE_FALLTHRU);

  make_edge (iter_part_bb, seq_start_bb, EDGE_TRUE_VALUE);
  make_edge (iter_part_bb, fin_bb, EDGE_FALSE_VALUE);

  make_edge (seq_start_bb, body_bb, EDGE_FALLTHRU);

  remove_edge (single_succ_edge (cont_bb));
  make_edge (cont_bb, body_bb, EDGE_TRUE_VALUE);
  make_edge (cont_bb, trip_update_bb, EDGE_FALSE_VALUE);

  make_edge (trip_update_bb, iter_part_bb, EDGE_FALLTHRU);
}