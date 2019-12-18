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
 size_t BUILT_IN_STACK_RESTORE ; 
 size_t BUILT_IN_STACK_SAVE ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_stack_save_restore (tree *save, tree *restore)
{
  tree save_call, tmp_var;

  save_call =
      build_function_call_expr (implicit_built_in_decls[BUILT_IN_STACK_SAVE],
				NULL_TREE);
  tmp_var = create_tmp_var (ptr_type_node, "saved_stack");

  *save = build2 (MODIFY_EXPR, ptr_type_node, tmp_var, save_call);
  *restore =
    build_function_call_expr (implicit_built_in_decls[BUILT_IN_STACK_RESTORE],
			      tree_cons (NULL_TREE, tmp_var, NULL_TREE));
}