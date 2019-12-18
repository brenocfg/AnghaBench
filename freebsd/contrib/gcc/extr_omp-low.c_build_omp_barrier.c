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
 size_t BUILT_IN_GOMP_BARRIER ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * built_in_decls ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_omp_barrier (tree *stmt_list)
{
  tree t;

  t = built_in_decls[BUILT_IN_GOMP_BARRIER];
  t = build_function_call_expr (t, NULL);
  gimplify_and_add (t, stmt_list);
}