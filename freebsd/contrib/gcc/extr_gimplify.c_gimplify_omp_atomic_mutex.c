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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;

/* Variables and functions */
 size_t BUILT_IN_GOMP_ATOMIC_END ; 
 size_t BUILT_IN_GOMP_ATOMIC_START ; 
 int GS_ALL_DONE ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/ * build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_fold_indirect_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_function_call_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** built_in_decls ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static enum gimplify_status
gimplify_omp_atomic_mutex (tree *expr_p, tree *pre_p, tree addr, tree rhs)
{
  tree t;

  t = built_in_decls[BUILT_IN_GOMP_ATOMIC_START];
  t = build_function_call_expr (t, NULL);
  gimplify_and_add (t, pre_p);

  t = build_fold_indirect_ref (addr);
  t = build2 (MODIFY_EXPR, void_type_node, t, rhs);
  gimplify_and_add (t, pre_p);
  
  t = built_in_decls[BUILT_IN_GOMP_ATOMIC_END];
  t = build_function_call_expr (t, NULL);
  gimplify_and_add (t, pre_p);

  *expr_p = NULL;
  return GS_ALL_DONE;
}