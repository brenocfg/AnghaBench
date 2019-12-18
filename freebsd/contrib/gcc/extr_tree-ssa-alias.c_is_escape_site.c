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
typedef  enum escape_type { ____Placeholder_escape_type } escape_type ;

/* Variables and functions */
 scalar_t__ ASM_EXPR ; 
 scalar_t__ CONVERT_EXPR ; 
 int ESCAPE_BAD_CAST ; 
 int ESCAPE_STORED_IN_GLOBAL ; 
 int ESCAPE_TO_ASM ; 
 int ESCAPE_TO_CALL ; 
 int ESCAPE_TO_PURE_CONST ; 
 int ESCAPE_TO_RETURN ; 
 int ESCAPE_UNKNOWN ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int NO_ESCAPE ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ RETURN_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_REF_CAN_ALIAS_ALL (scalar_t__) ; 
 scalar_t__ VIEW_CONVERT_EXPR ; 
 scalar_t__ get_base_address (scalar_t__) ; 
 scalar_t__ get_call_expr_in (scalar_t__) ; 

enum escape_type
is_escape_site (tree stmt)
{
  tree call = get_call_expr_in (stmt);
  if (call != NULL_TREE)
    {
      if (!TREE_SIDE_EFFECTS (call))
	return ESCAPE_TO_PURE_CONST;

      return ESCAPE_TO_CALL;
    }
  else if (TREE_CODE (stmt) == ASM_EXPR)
    return ESCAPE_TO_ASM;
  else if (TREE_CODE (stmt) == MODIFY_EXPR)
    {
      tree lhs = TREE_OPERAND (stmt, 0);

      /* Get to the base of _REF nodes.  */
      if (TREE_CODE (lhs) != SSA_NAME)
	lhs = get_base_address (lhs);

      /* If we couldn't recognize the LHS of the assignment, assume that it
	 is a non-local store.  */
      if (lhs == NULL_TREE)
	return ESCAPE_UNKNOWN;

      if (TREE_CODE (TREE_OPERAND (stmt, 1)) == NOP_EXPR
	  || TREE_CODE (TREE_OPERAND (stmt, 1)) == CONVERT_EXPR
	  || TREE_CODE (TREE_OPERAND (stmt, 1)) == VIEW_CONVERT_EXPR)
	{
	  tree from = TREE_TYPE (TREE_OPERAND (TREE_OPERAND (stmt, 1), 0));
	  tree to = TREE_TYPE (TREE_OPERAND (stmt, 1));

	  /* If the RHS is a conversion between a pointer and an integer, the
	     pointer escapes since we can't track the integer.  */
	  if (POINTER_TYPE_P (from) && !POINTER_TYPE_P (to))
	    return ESCAPE_BAD_CAST;

	  /* Same if the RHS is a conversion between a regular pointer and a
	     ref-all pointer since we can't track the SMT of the former.  */
	  if (POINTER_TYPE_P (from) && !TYPE_REF_CAN_ALIAS_ALL (from)
	      && POINTER_TYPE_P (to) && TYPE_REF_CAN_ALIAS_ALL (to))
	    return ESCAPE_BAD_CAST;
	}

      /* If the LHS is an SSA name, it can't possibly represent a non-local
	 memory store.  */
      if (TREE_CODE (lhs) == SSA_NAME)
	return NO_ESCAPE;

      /* FIXME: LHS is not an SSA_NAME.  Even if it's an assignment to a
	 local variables we cannot be sure if it will escape, because we
	 don't have information about objects not in SSA form.  Need to
	 implement something along the lines of

	 J.-D. Choi, M. Gupta, M. J. Serrano, V. C. Sreedhar, and S. P.
	 Midkiff, ``Escape analysis for java,'' in Proceedings of the
	 Conference on Object-Oriented Programming Systems, Languages, and
	 Applications (OOPSLA), pp. 1-19, 1999.  */
      return ESCAPE_STORED_IN_GLOBAL;
    }
  else if (TREE_CODE (stmt) == RETURN_EXPR)
    return ESCAPE_TO_RETURN;

  return NO_ESCAPE;
}