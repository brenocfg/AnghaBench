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
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ OFFSET_REF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decay_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_member_function_from_ptrfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

tree
build_addr_func (tree function)
{
  tree type = TREE_TYPE (function);

  /* We have to do these by hand to avoid real pointer to member
     functions.  */
  if (TREE_CODE (type) == METHOD_TYPE)
    {
      if (TREE_CODE (function) == OFFSET_REF)
	{
	  tree object = build_address (TREE_OPERAND (function, 0));
	  return get_member_function_from_ptrfunc (&object,
						   TREE_OPERAND (function, 1));
	}
      function = build_address (function);
    }
  else
    function = decay_conversion (function);

  return function;
}