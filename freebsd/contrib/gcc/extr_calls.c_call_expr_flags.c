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
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int flags_from_decl_or_type (scalar_t__) ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 

int
call_expr_flags (tree t)
{
  int flags;
  tree decl = get_callee_fndecl (t);

  if (decl)
    flags = flags_from_decl_or_type (decl);
  else
    {
      t = TREE_TYPE (TREE_OPERAND (t, 0));
      if (t && TREE_CODE (t) == POINTER_TYPE)
	flags = flags_from_decl_or_type (TREE_TYPE (t));
      else
	flags = 0;
    }

  return flags;
}