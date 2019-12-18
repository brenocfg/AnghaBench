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
 int /*<<< orphan*/  build_cxx_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_reference_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_type_info_type_node ; 
 int /*<<< orphan*/  get_global_value_if_present (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  push_throw_library_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_list_node ; 

__attribute__((used)) static tree
throw_bad_typeid (void)
{
  tree fn = get_identifier ("__cxa_bad_typeid");
  if (!get_global_value_if_present (fn, &fn))
    {
      tree t;

      t = build_reference_type (const_type_info_type_node);
      t = build_function_type (t, void_list_node);
      fn = push_throw_library_fn (fn, t);
    }

  return build_cxx_call (fn, NULL_TREE);
}