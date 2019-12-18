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
#define  ALIGNOF_EXPR 147 
#define  CALL_EXPR 146 
#define  CAST_EXPR 145 
#define  COMPONENT_REF 144 
#define  CONST_CAST_EXPR 143 
#define  CONST_DECL 142 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_PARM_P (int /*<<< orphan*/ ) ; 
#define  DYNAMIC_CAST_EXPR 141 
#define  IDENTIFIER_NODE 140 
 int /*<<< orphan*/  INTEGRAL_OR_ENUMERATION_TYPE_P (int /*<<< orphan*/ ) ; 
#define  MODOP_EXPR 139 
#define  REINTERPRET_CAST_EXPR 138 
#define  SCOPE_REF 137 
#define  SIZEOF_EXPR 136 
#define  STATIC_CAST_EXPR 135 
#define  TEMPLATE_PARM_INDEX 134 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CODE_CLASS (int) ; 
 int TREE_CODE_LENGTH (int) ; 
 int TREE_LIST ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 133 
 int any_value_dependent_elements_p (int /*<<< orphan*/ ) ; 
 int dependent_scope_ref_p (int /*<<< orphan*/ ,int (*) (int /*<<< orphan*/ )) ; 
 int dependent_type_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processing_template_decl ; 
#define  tcc_binary 132 
#define  tcc_comparison 131 
#define  tcc_expression 130 
#define  tcc_reference 129 
#define  tcc_unary 128 
 int type_dependent_expression_p (int /*<<< orphan*/ ) ; 

bool
value_dependent_expression_p (tree expression)
{
  if (!processing_template_decl)
    return false;

  /* A name declared with a dependent type.  */
  if (DECL_P (expression) && type_dependent_expression_p (expression))
    return true;

  switch (TREE_CODE (expression))
    {
    case IDENTIFIER_NODE:
      /* A name that has not been looked up -- must be dependent.  */
      return true;

    case TEMPLATE_PARM_INDEX:
      /* A non-type template parm.  */
      return true;

    case CONST_DECL:
      /* A non-type template parm.  */
      if (DECL_TEMPLATE_PARM_P (expression))
	return true;
      return false;

    case VAR_DECL:
       /* A constant with integral or enumeration type and is initialized
	  with an expression that is value-dependent.  */
      if (DECL_INITIAL (expression)
	  && INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (expression))
	  && value_dependent_expression_p (DECL_INITIAL (expression)))
	return true;
      return false;

    case DYNAMIC_CAST_EXPR:
    case STATIC_CAST_EXPR:
    case CONST_CAST_EXPR:
    case REINTERPRET_CAST_EXPR:
    case CAST_EXPR:
      /* These expressions are value-dependent if the type to which
	 the cast occurs is dependent or the expression being casted
	 is value-dependent.  */
      {
	tree type = TREE_TYPE (expression);

	if (dependent_type_p (type))
	  return true;

	/* A functional cast has a list of operands.  */
	expression = TREE_OPERAND (expression, 0);
	if (!expression)
	  {
	    /* If there are no operands, it must be an expression such
	       as "int()". This should not happen for aggregate types
	       because it would form non-constant expressions.  */
	    gcc_assert (INTEGRAL_OR_ENUMERATION_TYPE_P (type));

	    return false;
	  }

	if (TREE_CODE (expression) == TREE_LIST)
	  return any_value_dependent_elements_p (expression);

	return value_dependent_expression_p (expression);
      }

    case SIZEOF_EXPR:
    case ALIGNOF_EXPR:
      /* A `sizeof' expression is value-dependent if the operand is
	 type-dependent.  */
      expression = TREE_OPERAND (expression, 0);
      if (TYPE_P (expression))
	return dependent_type_p (expression);
      return type_dependent_expression_p (expression);

    case SCOPE_REF:
      return dependent_scope_ref_p (expression, value_dependent_expression_p);

    case COMPONENT_REF:
      return (value_dependent_expression_p (TREE_OPERAND (expression, 0))
	      || value_dependent_expression_p (TREE_OPERAND (expression, 1)));

    case CALL_EXPR:
      /* A CALL_EXPR may appear in a constant expression if it is a
	 call to a builtin function, e.g., __builtin_constant_p.  All
	 such calls are value-dependent.  */
      return true;

    case MODOP_EXPR:
      return ((value_dependent_expression_p (TREE_OPERAND (expression, 0)))
	      || (value_dependent_expression_p (TREE_OPERAND (expression, 2))));

    default:
      /* A constant expression is value-dependent if any subexpression is
	 value-dependent.  */
      switch (TREE_CODE_CLASS (TREE_CODE (expression)))
	{
	case tcc_reference:
	case tcc_unary:
	  return (value_dependent_expression_p
		  (TREE_OPERAND (expression, 0)));

	case tcc_comparison:
	case tcc_binary:
	  return ((value_dependent_expression_p
		   (TREE_OPERAND (expression, 0)))
		  || (value_dependent_expression_p
		      (TREE_OPERAND (expression, 1))));

	case tcc_expression:
	  {
	    int i;
	    for (i = 0; i < TREE_CODE_LENGTH (TREE_CODE (expression)); ++i)
	      /* In some cases, some of the operands may be missing.
		 (For example, in the case of PREDECREMENT_EXPR, the
		 amount to increment by may be missing.)  That doesn't
		 make the expression dependent.  */
	      if (TREE_OPERAND (expression, i)
		  && (value_dependent_expression_p
		      (TREE_OPERAND (expression, i))))
		return true;
	    return false;
	  }

	default:
	  break;
	}
    }

  /* The expression is not value-dependent.  */
  return false;
}