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
#define  ALIGNOF_EXPR 159 
#define  BASELINK 158 
 int /*<<< orphan*/  BASELINK_ACCESS_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  BASELINK_BINFO (scalar_t__) ; 
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
#define  CALL_EXPR 157 
#define  COMPLEX_CST 156 
#define  COMPONENT_REF 155 
#define  CONSTRUCTOR 154 
#define  CONST_DECL 153 
 int CONVERT_EXPR ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL_SET_P (scalar_t__) ; 
#define  FUNCTION_DECL 152 
#define  IDENTIFIER_NODE 151 
#define  INTEGER_CST 150 
 int NON_LVALUE_EXPR ; 
 int NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  OVERLOAD 149 
 scalar_t__ OVL_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  OVL_FUNCTION (scalar_t__) ; 
#define  PARM_DECL 148 
#define  PTRMEM_CST 147 
 scalar_t__ PTRMEM_CST_CLASS (scalar_t__) ; 
 int /*<<< orphan*/  PTRMEM_CST_MEMBER (scalar_t__) ; 
#define  REAL_CST 146 
 int REAL_VALUES_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SAVE_EXPR 145 
#define  SIZEOF_EXPR 144 
#define  SSA_NAME 143 
#define  STRING_CST 142 
#define  TARGET_EXPR 141 
#define  TEMPLATE_DECL 140 
#define  TEMPLATE_ID_EXPR 139 
 scalar_t__ TEMPLATE_PARM_DECL (scalar_t__) ; 
 int /*<<< orphan*/  TEMPLATE_PARM_IDX (scalar_t__) ; 
#define  TEMPLATE_PARM_INDEX 138 
 int /*<<< orphan*/  TEMPLATE_PARM_LEVEL (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TREE_CODE_CLASS (int) ; 
 int TREE_CODE_LENGTH (int) ; 
 scalar_t__ TREE_IMAGPART (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (scalar_t__) ; 
#define  TREE_LIST 137 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_REALPART (scalar_t__) ; 
 int /*<<< orphan*/  TREE_REAL_CST (scalar_t__) ; 
 int /*<<< orphan*/  TREE_STRING_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_STRING_POINTER (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TREE_VEC_ELT (scalar_t__,unsigned int) ; 
 unsigned int TREE_VEC_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_P (scalar_t__) ; 
#define  VAR_DECL 136 
#define  WITH_CLEANUP_EXPR 135 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int same_type_p (scalar_t__,scalar_t__) ; 
#define  tcc_binary 134 
#define  tcc_comparison 133 
#define  tcc_expression 132 
#define  tcc_reference 131 
#define  tcc_statement 130 
#define  tcc_type 129 
#define  tcc_unary 128 

bool
cp_tree_equal (tree t1, tree t2)
{
  enum tree_code code1, code2;

  if (t1 == t2)
    return true;
  if (!t1 || !t2)
    return false;

  for (code1 = TREE_CODE (t1);
       code1 == NOP_EXPR || code1 == CONVERT_EXPR
	 || code1 == NON_LVALUE_EXPR;
       code1 = TREE_CODE (t1))
    t1 = TREE_OPERAND (t1, 0);
  for (code2 = TREE_CODE (t2);
       code2 == NOP_EXPR || code2 == CONVERT_EXPR
	 || code1 == NON_LVALUE_EXPR;
       code2 = TREE_CODE (t2))
    t2 = TREE_OPERAND (t2, 0);

  /* They might have become equal now.  */
  if (t1 == t2)
    return true;

  if (code1 != code2)
    return false;

  switch (code1)
    {
    case INTEGER_CST:
      return TREE_INT_CST_LOW (t1) == TREE_INT_CST_LOW (t2)
	&& TREE_INT_CST_HIGH (t1) == TREE_INT_CST_HIGH (t2);

    case REAL_CST:
      return REAL_VALUES_EQUAL (TREE_REAL_CST (t1), TREE_REAL_CST (t2));

    case STRING_CST:
      return TREE_STRING_LENGTH (t1) == TREE_STRING_LENGTH (t2)
	&& !memcmp (TREE_STRING_POINTER (t1), TREE_STRING_POINTER (t2),
		    TREE_STRING_LENGTH (t1));

    case COMPLEX_CST:
      return cp_tree_equal (TREE_REALPART (t1), TREE_REALPART (t2))
	&& cp_tree_equal (TREE_IMAGPART (t1), TREE_IMAGPART (t2));

    case CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      if (!(same_type_p (TREE_TYPE (t1), TREE_TYPE (t2))
	    /* The first operand is RTL.  */
	    && TREE_OPERAND (t1, 0) == TREE_OPERAND (t2, 0)))
	return false;
      return cp_tree_equal (TREE_OPERAND (t1, 1), TREE_OPERAND (t2, 1));

    case TREE_LIST:
      if (!cp_tree_equal (TREE_PURPOSE (t1), TREE_PURPOSE (t2)))
	return false;
      if (!cp_tree_equal (TREE_VALUE (t1), TREE_VALUE (t2)))
	return false;
      return cp_tree_equal (TREE_CHAIN (t1), TREE_CHAIN (t2));

    case SAVE_EXPR:
      return cp_tree_equal (TREE_OPERAND (t1, 0), TREE_OPERAND (t2, 0));

    case CALL_EXPR:
      if (!cp_tree_equal (TREE_OPERAND (t1, 0), TREE_OPERAND (t2, 0)))
	return false;
      return cp_tree_equal (TREE_OPERAND (t1, 1), TREE_OPERAND (t2, 1));

    case TARGET_EXPR:
      {
	tree o1 = TREE_OPERAND (t1, 0);
	tree o2 = TREE_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	if (TREE_CODE (o1) == VAR_DECL && DECL_NAME (o1) == NULL_TREE
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	else if (TREE_CODE (o2) == VAR_DECL && DECL_NAME (o2) == NULL_TREE
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	else if (!cp_tree_equal (o1, o2))
	  return false;

	return cp_tree_equal (TREE_OPERAND (t1, 1), TREE_OPERAND (t2, 1));
      }

    case WITH_CLEANUP_EXPR:
      if (!cp_tree_equal (TREE_OPERAND (t1, 0), TREE_OPERAND (t2, 0)))
	return false;
      return cp_tree_equal (TREE_OPERAND (t1, 1), TREE_OPERAND (t1, 1));

    case COMPONENT_REF:
      if (TREE_OPERAND (t1, 1) != TREE_OPERAND (t2, 1))
	return false;
      return cp_tree_equal (TREE_OPERAND (t1, 0), TREE_OPERAND (t2, 0));

    case VAR_DECL:
    case PARM_DECL:
    case CONST_DECL:
    case FUNCTION_DECL:
    case TEMPLATE_DECL:
    case IDENTIFIER_NODE:
    case SSA_NAME:
      return false;

    case BASELINK:
      return (BASELINK_BINFO (t1) == BASELINK_BINFO (t2)
	      && BASELINK_ACCESS_BINFO (t1) == BASELINK_ACCESS_BINFO (t2)
	      && cp_tree_equal (BASELINK_FUNCTIONS (t1),
				BASELINK_FUNCTIONS (t2)));

    case TEMPLATE_PARM_INDEX:
      return (TEMPLATE_PARM_IDX (t1) == TEMPLATE_PARM_IDX (t2)
	      && TEMPLATE_PARM_LEVEL (t1) == TEMPLATE_PARM_LEVEL (t2)
	      && same_type_p (TREE_TYPE (TEMPLATE_PARM_DECL (t1)),
			      TREE_TYPE (TEMPLATE_PARM_DECL (t2))));

    case TEMPLATE_ID_EXPR:
      {
	unsigned ix;
	tree vec1, vec2;

	if (!cp_tree_equal (TREE_OPERAND (t1, 0), TREE_OPERAND (t2, 0)))
	  return false;
	vec1 = TREE_OPERAND (t1, 1);
	vec2 = TREE_OPERAND (t2, 1);

	if (!vec1 || !vec2)
	  return !vec1 && !vec2;

	if (TREE_VEC_LENGTH (vec1) != TREE_VEC_LENGTH (vec2))
	  return false;

	for (ix = TREE_VEC_LENGTH (vec1); ix--;)
	  if (!cp_tree_equal (TREE_VEC_ELT (vec1, ix),
			      TREE_VEC_ELT (vec2, ix)))
	    return false;

	return true;
      }

    case SIZEOF_EXPR:
    case ALIGNOF_EXPR:
      {
	tree o1 = TREE_OPERAND (t1, 0);
	tree o2 = TREE_OPERAND (t2, 0);

	if (TREE_CODE (o1) != TREE_CODE (o2))
	  return false;
	if (TYPE_P (o1))
	  return same_type_p (o1, o2);
	else
	  return cp_tree_equal (o1, o2);
      }

    case PTRMEM_CST:
      /* Two pointer-to-members are the same if they point to the same
	 field or function in the same class.  */
      if (PTRMEM_CST_MEMBER (t1) != PTRMEM_CST_MEMBER (t2))
	return false;

      return same_type_p (PTRMEM_CST_CLASS (t1), PTRMEM_CST_CLASS (t2));

    case OVERLOAD:
      if (OVL_FUNCTION (t1) != OVL_FUNCTION (t2))
	return false;
      return cp_tree_equal (OVL_CHAIN (t1), OVL_CHAIN (t2));

    default:
      break;
    }

  switch (TREE_CODE_CLASS (code1))
    {
    case tcc_unary:
    case tcc_binary:
    case tcc_comparison:
    case tcc_expression:
    case tcc_reference:
    case tcc_statement:
      {
	int i;

	for (i = 0; i < TREE_CODE_LENGTH (code1); ++i)
	  if (!cp_tree_equal (TREE_OPERAND (t1, i), TREE_OPERAND (t2, i)))
	    return false;

	return true;
      }

    case tcc_type:
      return same_type_p (t1, t2);
    default:
      gcc_unreachable ();
    }
  /* We can get here with --disable-checking.  */
  return false;
}