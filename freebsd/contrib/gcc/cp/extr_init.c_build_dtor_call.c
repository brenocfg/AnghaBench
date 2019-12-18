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
typedef  int special_function_kind ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_dtor_identifier ; 
 int /*<<< orphan*/  build_new_method_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_dtor_identifier ; 
 int /*<<< orphan*/  deleting_dtor_identifier ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  lookup_fnfields (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  sfk_base_destructor 130 
#define  sfk_complete_destructor 129 
#define  sfk_deleting_destructor 128 

__attribute__((used)) static tree
build_dtor_call (tree exp, special_function_kind dtor_kind, int flags)
{
  tree name;
  tree fn;
  switch (dtor_kind)
    {
    case sfk_complete_destructor:
      name = complete_dtor_identifier;
      break;

    case sfk_base_destructor:
      name = base_dtor_identifier;
      break;

    case sfk_deleting_destructor:
      name = deleting_dtor_identifier;
      break;

    default:
      gcc_unreachable ();
    }
  fn = lookup_fnfields (TREE_TYPE (exp), name, /*protect=*/2);
  return build_new_method_call (exp, fn,
				/*args=*/NULL_TREE,
				/*conversion_path=*/NULL_TREE,
				flags,
				/*fn_p=*/NULL);
}