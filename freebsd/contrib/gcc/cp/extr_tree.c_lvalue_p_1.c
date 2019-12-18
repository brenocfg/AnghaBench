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
typedef  int cp_lvalue_kind ;

/* Variables and functions */
#define  ARRAY_REF 153 
#define  CALL_EXPR 152 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
#define  COMPONENT_REF 151 
#define  COMPOUND_EXPR 150 
#define  COND_EXPR 149 
#define  CONST_DECL 148 
 int /*<<< orphan*/  DECL_C_BIT_FIELD (scalar_t__) ; 
 int /*<<< orphan*/  DECL_IN_AGGR_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_LANG_SPECIFIC (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NONSTATIC_MEMBER_FUNCTION_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_PACKED (scalar_t__) ; 
 int FIELD_DECL ; 
#define  FUNCTION_DECL 147 
#define  IMAGPART_EXPR 146 
#define  INDIRECT_REF 145 
#define  MAX_EXPR 144 
 int METHOD_TYPE ; 
#define  MIN_EXPR 143 
#define  MODIFY_EXPR 142 
#define  NON_DEPENDENT_EXPR 141 
#define  PARM_DECL 140 
#define  PREDECREMENT_EXPR 139 
#define  PREINCREMENT_EXPR 138 
#define  REALPART_EXPR 137 
 int REFERENCE_TYPE ; 
#define  RESULT_DECL 136 
#define  SAVE_EXPR 135 
#define  SCOPE_REF 134 
#define  STRING_CST 133 
#define  TARGET_EXPR 132 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_READONLY (scalar_t__) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 int /*<<< orphan*/  TREE_STATIC (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TRY_CATCH_EXPR 131 
#define  VAR_DECL 130 
#define  VA_ARG_EXPR 129 
#define  WITH_CLEANUP_EXPR 128 
 int clk_bitfield ; 
 int clk_class ; 
 int clk_none ; 
 int clk_ordinary ; 
 int clk_packed ; 
 scalar_t__ current_class_ptr ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static cp_lvalue_kind
lvalue_p_1 (tree ref,
	    int treat_class_rvalues_as_lvalues)
{
  cp_lvalue_kind op1_lvalue_kind = clk_none;
  cp_lvalue_kind op2_lvalue_kind = clk_none;

  if (TREE_CODE (TREE_TYPE (ref)) == REFERENCE_TYPE)
    return clk_ordinary;

  if (ref == current_class_ptr)
    return clk_none;

  switch (TREE_CODE (ref))
    {
      /* preincrements and predecrements are valid lvals, provided
	 what they refer to are valid lvals.  */
    case PREINCREMENT_EXPR:
    case PREDECREMENT_EXPR:
    case SAVE_EXPR:
    case TRY_CATCH_EXPR:
    case WITH_CLEANUP_EXPR:
    case REALPART_EXPR:
    case IMAGPART_EXPR:
      return lvalue_p_1 (TREE_OPERAND (ref, 0),
			 treat_class_rvalues_as_lvalues);

    case COMPONENT_REF:
      op1_lvalue_kind = lvalue_p_1 (TREE_OPERAND (ref, 0),
				    treat_class_rvalues_as_lvalues);
      /* Look at the member designator.  */
      if (!op1_lvalue_kind
	  /* The "field" can be a FUNCTION_DECL or an OVERLOAD in some
	     situations.  */
	  || TREE_CODE (TREE_OPERAND (ref, 1)) != FIELD_DECL)
	;
      else if (DECL_C_BIT_FIELD (TREE_OPERAND (ref, 1)))
	{
	  /* Clear the ordinary bit.  If this object was a class
	     rvalue we want to preserve that information.  */
	  op1_lvalue_kind &= ~clk_ordinary;
	  /* The lvalue is for a bitfield.  */
	  op1_lvalue_kind |= clk_bitfield;
	}
      else if (DECL_PACKED (TREE_OPERAND (ref, 1)))
	op1_lvalue_kind |= clk_packed;

      return op1_lvalue_kind;

    case STRING_CST:
      return clk_ordinary;

    case CONST_DECL:
    case VAR_DECL:
      if (TREE_READONLY (ref) && ! TREE_STATIC (ref)
	  && DECL_LANG_SPECIFIC (ref)
	  && DECL_IN_AGGR_P (ref))
	return clk_none;
    case INDIRECT_REF:
    case ARRAY_REF:
    case PARM_DECL:
    case RESULT_DECL:
      if (TREE_CODE (TREE_TYPE (ref)) != METHOD_TYPE)
	return clk_ordinary;
      break;

      /* A currently unresolved scope ref.  */
    case SCOPE_REF:
      gcc_unreachable ();
    case MAX_EXPR:
    case MIN_EXPR:
      /* Disallow <? and >? as lvalues if either argument side-effects.  */
      if (TREE_SIDE_EFFECTS (TREE_OPERAND (ref, 0))
	  || TREE_SIDE_EFFECTS (TREE_OPERAND (ref, 1)))
	return clk_none;
      op1_lvalue_kind = lvalue_p_1 (TREE_OPERAND (ref, 0),
				    treat_class_rvalues_as_lvalues);
      op2_lvalue_kind = lvalue_p_1 (TREE_OPERAND (ref, 1),
				    treat_class_rvalues_as_lvalues);
      break;

    case COND_EXPR:
      op1_lvalue_kind = lvalue_p_1 (TREE_OPERAND (ref, 1),
				    treat_class_rvalues_as_lvalues);
      op2_lvalue_kind = lvalue_p_1 (TREE_OPERAND (ref, 2),
				    treat_class_rvalues_as_lvalues);
      break;

    case MODIFY_EXPR:
      return clk_ordinary;

    case COMPOUND_EXPR:
      return lvalue_p_1 (TREE_OPERAND (ref, 1),
			 treat_class_rvalues_as_lvalues);

    case TARGET_EXPR:
      return treat_class_rvalues_as_lvalues ? clk_class : clk_none;

    case VA_ARG_EXPR:
      return (treat_class_rvalues_as_lvalues
	      && CLASS_TYPE_P (TREE_TYPE (ref))
	      ? clk_class : clk_none);

    case CALL_EXPR:
      /* Any class-valued call would be wrapped in a TARGET_EXPR.  */
      return clk_none;

    case FUNCTION_DECL:
      /* All functions (except non-static-member functions) are
	 lvalues.  */
      return (DECL_NONSTATIC_MEMBER_FUNCTION_P (ref)
	      ? clk_none : clk_ordinary);

    case NON_DEPENDENT_EXPR:
      /* We must consider NON_DEPENDENT_EXPRs to be lvalues so that
	 things like "&E" where "E" is an expression with a
	 non-dependent type work. It is safe to be lenient because an
	 error will be issued when the template is instantiated if "E"
	 is not an lvalue.  */
      return clk_ordinary;

    default:
      break;
    }

  /* If one operand is not an lvalue at all, then this expression is
     not an lvalue.  */
  if (!op1_lvalue_kind || !op2_lvalue_kind)
    return clk_none;

  /* Otherwise, it's an lvalue, and it has all the odd properties
     contributed by either operand.  */
  op1_lvalue_kind = op1_lvalue_kind | op2_lvalue_kind;
  /* It's not an ordinary lvalue if it involves either a bit-field or
     a class rvalue.  */
  if ((op1_lvalue_kind & ~clk_ordinary) != clk_none)
    op1_lvalue_kind &= ~clk_ordinary;
  return op1_lvalue_kind;
}