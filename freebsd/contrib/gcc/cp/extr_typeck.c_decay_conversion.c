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
 int /*<<< orphan*/  ADDR_EXPR ; 
 int ARRAY_TYPE ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 int COMPOUND_EXPR ; 
 int CONSTRUCTOR ; 
 int FUNCTION_TYPE ; 
 int INDIRECT_REF ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_STATIC (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int VAR_DECL ; 
 int VOID_TYPE ; 
 scalar_t__ build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_address (scalar_t__) ; 
 scalar_t__ build_nop (scalar_t__,scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ convert_bitfield_to_declared_type (scalar_t__) ; 
 scalar_t__ cp_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_type_quals (scalar_t__) ; 
 int /*<<< orphan*/  cxx_incomplete_type_error (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cxx_mark_addressable (scalar_t__) ; 
 scalar_t__ decl_constant_value (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 scalar_t__ invalid_nonstatic_memfn_p (scalar_t__) ; 
 scalar_t__ is_overloaded_fn (scalar_t__) ; 
 int /*<<< orphan*/  lvalue_p (scalar_t__) ; 
 scalar_t__ type_unknown_p (scalar_t__) ; 

tree
decay_conversion (tree exp)
{
  tree type;
  enum tree_code code;

  type = TREE_TYPE (exp);
  if (type == error_mark_node)
    return error_mark_node;

  if (type_unknown_p (exp))
    {
      cxx_incomplete_type_error (exp, TREE_TYPE (exp));
      return error_mark_node;
    }

  exp = decl_constant_value (exp);
  if (error_operand_p (exp))
    return error_mark_node;

  /* build_c_cast puts on a NOP_EXPR to make the result not an lvalue.
     Leave such NOP_EXPRs, since RHS is being used in non-lvalue context.  */
  code = TREE_CODE (type);
  if (code == VOID_TYPE)
    {
      error ("void value not ignored as it ought to be");
      return error_mark_node;
    }
  if (invalid_nonstatic_memfn_p (exp))
    return error_mark_node;
  if (code == FUNCTION_TYPE || is_overloaded_fn (exp))
    return build_unary_op (ADDR_EXPR, exp, 0);
  if (code == ARRAY_TYPE)
    {
      tree adr;
      tree ptrtype;

      if (TREE_CODE (exp) == INDIRECT_REF)
	return build_nop (build_pointer_type (TREE_TYPE (type)),
			  TREE_OPERAND (exp, 0));

      if (TREE_CODE (exp) == COMPOUND_EXPR)
	{
	  tree op1 = decay_conversion (TREE_OPERAND (exp, 1));
	  return build2 (COMPOUND_EXPR, TREE_TYPE (op1),
			 TREE_OPERAND (exp, 0), op1);
	}

      if (!lvalue_p (exp)
	  && ! (TREE_CODE (exp) == CONSTRUCTOR && TREE_STATIC (exp)))
	{
	  error ("invalid use of non-lvalue array");
	  return error_mark_node;
	}

      ptrtype = build_pointer_type (TREE_TYPE (type));

      if (TREE_CODE (exp) == VAR_DECL)
	{
	  if (!cxx_mark_addressable (exp))
	    return error_mark_node;
	  adr = build_nop (ptrtype, build_address (exp));
	  return adr;
	}
      /* This way is better for a COMPONENT_REF since it can
	 simplify the offset for a component.  */
      adr = build_unary_op (ADDR_EXPR, exp, 1);
      return cp_convert (ptrtype, adr);
    }

  /* If a bitfield is used in a context where integral promotion
     applies, then the caller is expected to have used
     default_conversion.  That function promotes bitfields correctly
     before calling this function.  At this point, if we have a
     bitfield referenced, we may assume that is not subject to
     promotion, and that, therefore, the type of the resulting rvalue
     is the declared type of the bitfield.  */
  exp = convert_bitfield_to_declared_type (exp);

  /* We do not call rvalue() here because we do not want to wrap EXP
     in a NON_LVALUE_EXPR.  */

  /* [basic.lval]

     Non-class rvalues always have cv-unqualified types.  */
  type = TREE_TYPE (exp);
  if (!CLASS_TYPE_P (type) && cp_type_quals (type))
    exp = build_nop (TYPE_MAIN_VARIANT (type), exp);

  return exp;
}