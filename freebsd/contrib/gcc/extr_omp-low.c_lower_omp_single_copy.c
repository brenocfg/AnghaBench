#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_4__ {void* sender_decl; void* receiver_decl; int /*<<< orphan*/ * record_type; } ;
typedef  TYPE_1__ omp_context ;

/* Variables and functions */
 size_t BUILT_IN_GOMP_SINGLE_COPY_END ; 
 size_t BUILT_IN_GOMP_SINGLE_COPY_START ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/ * OMP_SINGLE_BODY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMP_SINGLE_CLAUSES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/ * build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_and_jump (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * build_fold_addr_expr (void*) ; 
 int /*<<< orphan*/ * build_function_call_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_int_cst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_pointer_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** built_in_decls ; 
 int /*<<< orphan*/ * create_artificial_label () ; 
 void* create_tmp_var (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fold_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lower_copyprivate_clauses (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_omp_single_copy (tree single_stmt, tree *pre_p, omp_context *ctx)
{
  tree ptr_type, t, args, l0, l1, l2, copyin_seq;

  ctx->sender_decl = create_tmp_var (ctx->record_type, ".omp_copy_o");

  ptr_type = build_pointer_type (ctx->record_type);
  ctx->receiver_decl = create_tmp_var (ptr_type, ".omp_copy_i");

  l0 = create_artificial_label ();
  l1 = create_artificial_label ();
  l2 = create_artificial_label ();

  t = built_in_decls[BUILT_IN_GOMP_SINGLE_COPY_START];
  t = build_function_call_expr (t, NULL);
  t = fold_convert (ptr_type, t);
  t = build2 (MODIFY_EXPR, void_type_node, ctx->receiver_decl, t);
  gimplify_and_add (t, pre_p);

  t = build2 (EQ_EXPR, boolean_type_node, ctx->receiver_decl,
	      build_int_cst (ptr_type, 0));
  t = build3 (COND_EXPR, void_type_node, t,
	      build_and_jump (&l0), build_and_jump (&l1));
  gimplify_and_add (t, pre_p);

  t = build1 (LABEL_EXPR, void_type_node, l0);
  gimplify_and_add (t, pre_p);

  append_to_statement_list (OMP_SINGLE_BODY (single_stmt), pre_p);

  copyin_seq = NULL;
  lower_copyprivate_clauses (OMP_SINGLE_CLAUSES (single_stmt), pre_p,
			      &copyin_seq, ctx);

  t = build_fold_addr_expr (ctx->sender_decl);
  args = tree_cons (NULL, t, NULL);
  t = built_in_decls[BUILT_IN_GOMP_SINGLE_COPY_END];
  t = build_function_call_expr (t, args);
  gimplify_and_add (t, pre_p);

  t = build_and_jump (&l2);
  gimplify_and_add (t, pre_p);

  t = build1 (LABEL_EXPR, void_type_node, l1);
  gimplify_and_add (t, pre_p);

  append_to_statement_list (copyin_seq, pre_p);

  t = build1 (LABEL_EXPR, void_type_node, l2);
  gimplify_and_add (t, pre_p);
}