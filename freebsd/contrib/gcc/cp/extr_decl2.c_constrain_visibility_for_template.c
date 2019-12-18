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
 scalar_t__ ADDR_EXPR ; 
 int DECL_VISIBILITY (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  INNERMOST_TEMPLATE_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ ,int) ; 
 int TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int VISIBILITY_ANON ; 
 int /*<<< orphan*/  constrain_visibility (int /*<<< orphan*/ ,int) ; 
 int type_visibility (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
constrain_visibility_for_template (tree decl, tree targs)
{
  /* If this is a template instantiation, check the innermost
     template args for visibility constraints.  The outer template
     args are covered by the class check.  */
  tree args = INNERMOST_TEMPLATE_ARGS (targs);
  int i;
  for (i = TREE_VEC_LENGTH (args); i > 0; --i)
    {
      int vis = 0;

      tree arg = TREE_VEC_ELT (args, i-1);
      if (TYPE_P (arg))
	vis = type_visibility (arg);
      else if (TREE_TYPE (arg) && POINTER_TYPE_P (TREE_TYPE (arg)))
	{
	  STRIP_NOPS (arg);
	  if (TREE_CODE (arg) == ADDR_EXPR)
	    arg = TREE_OPERAND (arg, 0);
	  if (TREE_CODE (arg) == VAR_DECL
	      || TREE_CODE (arg) == FUNCTION_DECL)
	    {
	      if (! TREE_PUBLIC (arg))
		vis = VISIBILITY_ANON;
	      else
		vis = DECL_VISIBILITY (arg);
	    }
	}
      if (vis)
	constrain_visibility (decl, vis);
    }
}