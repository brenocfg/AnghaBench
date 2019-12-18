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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_function_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_global_value_if_present (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  push_void_library_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_list_node ; 

__attribute__((used)) static tree
do_free_exception (tree ptr)
{
  tree fn;

  fn = get_identifier ("__cxa_free_exception");
  if (!get_global_value_if_present (fn, &fn))
    {
      /* Declare void __cxa_free_exception (void *).  */
      fn = push_void_library_fn (fn, tree_cons (NULL_TREE, ptr_type_node,
						void_list_node));
    }

  return build_function_call (fn, tree_cons (NULL_TREE, ptr, NULL_TREE));
}