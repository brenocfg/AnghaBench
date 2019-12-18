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
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ CONSTANT_CLASS_P (scalar_t__) ; 
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ STRING_CST ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_SIDE_EFFECTS (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ cfun ; 
 scalar_t__ folding_initializer ; 
 scalar_t__ integer_one_node ; 
 scalar_t__ integer_zero_node ; 
 scalar_t__ integer_zerop (scalar_t__) ; 

__attribute__((used)) static tree
fold_builtin_constant_p (tree arglist)
{
  if (arglist == 0)
    return 0;

  arglist = TREE_VALUE (arglist);

  /* We return 1 for a numeric type that's known to be a constant
     value at compile-time or for an aggregate type that's a
     literal constant.  */
  STRIP_NOPS (arglist);

  /* If we know this is a constant, emit the constant of one.  */
  if (CONSTANT_CLASS_P (arglist)
      || (TREE_CODE (arglist) == CONSTRUCTOR
	  && TREE_CONSTANT (arglist)))
    return integer_one_node;
  if (TREE_CODE (arglist) == ADDR_EXPR)
    {
       tree op = TREE_OPERAND (arglist, 0);
       if (TREE_CODE (op) == STRING_CST
	   || (TREE_CODE (op) == ARRAY_REF
	       && integer_zerop (TREE_OPERAND (op, 1))
	       && TREE_CODE (TREE_OPERAND (op, 0)) == STRING_CST))
	 return integer_one_node;
    }

  /* If this expression has side effects, show we don't know it to be a
     constant.  Likewise if it's a pointer or aggregate type since in
     those case we only want literals, since those are only optimized
     when generating RTL, not later.
     And finally, if we are compiling an initializer, not code, we
     need to return a definite result now; there's not going to be any
     more optimization done.  */
  if (TREE_SIDE_EFFECTS (arglist)
      || AGGREGATE_TYPE_P (TREE_TYPE (arglist))
      || POINTER_TYPE_P (TREE_TYPE (arglist))
      || cfun == 0
      || folding_initializer)
    return integer_zero_node;

  return 0;
}