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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 size_t BUILT_IN_GOMP_SINGLE_START ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  OMP_SINGLE_BODY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * built_in_decls ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_omp_single_simple (tree single_stmt, tree *pre_p)
{
  tree t;

  t = built_in_decls[BUILT_IN_GOMP_SINGLE_START];
  t = build_function_call_expr (t, NULL);
  t = build3 (COND_EXPR, void_type_node, t,
	      OMP_SINGLE_BODY (single_stmt), NULL);
  gimplify_and_add (t, pre_p);
}