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
 int ARRAY_TYPE ; 
 int CONV_FORCE_TEMP ; 
 int CONV_IMPLICIT ; 
 int ERROR_MARK ; 
 int FUNCTION_TYPE ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
 int METHOD_TYPE ; 
 int NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int REFERENCE_TYPE ; 
 int TREE_CODE (scalar_t__) ; 
 int TREE_LIST ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ complete_type (scalar_t__) ; 
 scalar_t__ convert_for_assignment (scalar_t__,scalar_t__,char const*,scalar_t__,int) ; 
 scalar_t__ decay_conversion (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,int,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int errorcount ; 
 scalar_t__ initialize_reference (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 scalar_t__ ocp_convert (scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ require_complete_type (scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int warningcount ; 

tree
convert_for_initialization (tree exp, tree type, tree rhs, int flags,
			    const char *errtype, tree fndecl, int parmnum)
{
  enum tree_code codel = TREE_CODE (type);
  tree rhstype;
  enum tree_code coder;

  /* build_c_cast puts on a NOP_EXPR to make the result not an lvalue.
     Strip such NOP_EXPRs, since RHS is used in non-lvalue context.  */
  if (TREE_CODE (rhs) == NOP_EXPR
      && TREE_TYPE (rhs) == TREE_TYPE (TREE_OPERAND (rhs, 0))
      && codel != REFERENCE_TYPE)
    rhs = TREE_OPERAND (rhs, 0);

  if (type == error_mark_node
      || rhs == error_mark_node
      || (TREE_CODE (rhs) == TREE_LIST && TREE_VALUE (rhs) == error_mark_node))
    return error_mark_node;

  if ((TREE_CODE (TREE_TYPE (rhs)) == ARRAY_TYPE
       && TREE_CODE (type) != ARRAY_TYPE
       && (TREE_CODE (type) != REFERENCE_TYPE
	   || TREE_CODE (TREE_TYPE (type)) != ARRAY_TYPE))
      || (TREE_CODE (TREE_TYPE (rhs)) == FUNCTION_TYPE
	  && (TREE_CODE (type) != REFERENCE_TYPE
	      || TREE_CODE (TREE_TYPE (type)) != FUNCTION_TYPE))
      || TREE_CODE (TREE_TYPE (rhs)) == METHOD_TYPE)
    rhs = decay_conversion (rhs);

  rhstype = TREE_TYPE (rhs);
  coder = TREE_CODE (rhstype);

  if (coder == ERROR_MARK)
    return error_mark_node;

  /* We accept references to incomplete types, so we can
     return here before checking if RHS is of complete type.  */

  if (codel == REFERENCE_TYPE)
    {
      /* This should eventually happen in convert_arguments.  */
      int savew = 0, savee = 0;

      if (fndecl)
	savew = warningcount, savee = errorcount;
      rhs = initialize_reference (type, rhs, /*decl=*/NULL_TREE,
				  /*cleanup=*/NULL);
      if (fndecl)
	{
	  if (warningcount > savew)
	    warning (0, "in passing argument %P of %q+D", parmnum, fndecl);
	  else if (errorcount > savee)
	    error ("in passing argument %P of %q+D", parmnum, fndecl);
	}
      return rhs;
    }

  if (exp != 0)
    exp = require_complete_type (exp);
  if (exp == error_mark_node)
    return error_mark_node;

  rhstype = non_reference (rhstype);

  type = complete_type (type);

  if (IS_AGGR_TYPE (type))
    return ocp_convert (type, rhs, CONV_IMPLICIT|CONV_FORCE_TEMP, flags);

  return convert_for_assignment (type, rhs, errtype, fndecl, parmnum);
}