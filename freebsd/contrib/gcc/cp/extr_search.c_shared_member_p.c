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
 scalar_t__ CONST_DECL ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (scalar_t__) ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ is_overloaded_fn (scalar_t__) ; 

int
shared_member_p (tree t)
{
  if (TREE_CODE (t) == VAR_DECL || TREE_CODE (t) == TYPE_DECL \
      || TREE_CODE (t) == CONST_DECL)
    return 1;
  if (is_overloaded_fn (t))
    {
      for (; t; t = OVL_NEXT (t))
	{
	  tree fn = OVL_CURRENT (t);
	  if (DECL_NONSTATIC_MEMBER_FUNCTION_P (fn))
	    return 0;
	}
      return 1;
    }
  return 0;
}