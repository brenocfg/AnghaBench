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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ NEGATE_EXPR ; 
 int PLUS_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 

__attribute__((used)) static tree
associate_trees (tree t1, tree t2, enum tree_code code, tree type)
{
  if (t1 == 0)
    return t2;
  else if (t2 == 0)
    return t1;

  /* If either input is CODE, a PLUS_EXPR, or a MINUS_EXPR, don't
     try to fold this since we will have infinite recursion.  But do
     deal with any NEGATE_EXPRs.  */
  if (TREE_CODE (t1) == code || TREE_CODE (t2) == code
      || TREE_CODE (t1) == MINUS_EXPR || TREE_CODE (t2) == MINUS_EXPR)
    {
      if (code == PLUS_EXPR)
	{
	  if (TREE_CODE (t1) == NEGATE_EXPR)
	    return build2 (MINUS_EXPR, type, fold_convert (type, t2),
			   fold_convert (type, TREE_OPERAND (t1, 0)));
	  else if (TREE_CODE (t2) == NEGATE_EXPR)
	    return build2 (MINUS_EXPR, type, fold_convert (type, t1),
			   fold_convert (type, TREE_OPERAND (t2, 0)));
	  else if (integer_zerop (t2))
	    return fold_convert (type, t1);
	}
      else if (code == MINUS_EXPR)
	{
	  if (integer_zerop (t2))
	    return fold_convert (type, t1);
	}

      return build2 (code, type, fold_convert (type, t1),
		     fold_convert (type, t2));
    }

  return fold_build2 (code, type, fold_convert (type, t1),
		      fold_convert (type, t2));
}