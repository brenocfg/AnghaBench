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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  check_function_arguments_recurse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  check_nonnull_arg ; 
 scalar_t__ is_attribute_p (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nonnull_check_p (scalar_t__,int) ; 

__attribute__((used)) static void
check_function_nonnull (tree attrs, tree params)
{
  tree a, args, param;
  int param_num;

  for (a = attrs; a; a = TREE_CHAIN (a))
    {
      if (is_attribute_p ("nonnull", TREE_PURPOSE (a)))
	{
	  args = TREE_VALUE (a);

	  /* Walk the argument list.  If we encounter an argument number we
	     should check for non-null, do it.  If the attribute has no args,
	     then every pointer argument is checked (in which case the check
	     for pointer type is done in check_nonnull_arg).  */
	  for (param = params, param_num = 1; ;
	       param_num++, param = TREE_CHAIN (param))
	    {
	      if (!param)
	break;
	      if (!args || nonnull_check_p (args, param_num))
	check_function_arguments_recurse (check_nonnull_arg, NULL,
					  TREE_VALUE (param),
					  param_num);
	    }
	}
    }
}