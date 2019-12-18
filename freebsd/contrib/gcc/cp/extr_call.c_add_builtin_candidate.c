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
struct z_candidate {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  ARITHMETIC_TYPE_P (scalar_t__) ; 
#define  ARRAY_REF 158 
#define  BIT_AND_EXPR 157 
#define  BIT_IOR_EXPR 156 
#define  BIT_NOT_EXPR 155 
#define  BIT_XOR_EXPR 154 
 scalar_t__ BOOLEAN_TYPE ; 
#define  COND_EXPR 153 
 int /*<<< orphan*/  DERIVED_FROM_P (scalar_t__,scalar_t__) ; 
 scalar_t__ ENUMERAL_TYPE ; 
#define  EQ_EXPR 152 
 scalar_t__ FUNCTION_TYPE ; 
#define  GE_EXPR 151 
#define  GT_EXPR 150 
#define  INDIRECT_REF 149 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
#define  LE_EXPR 148 
#define  LSHIFT_EXPR 147 
#define  LT_EXPR 146 
#define  MAX_EXPR 145 
#define  MEMBER_REF 144 
#define  MINUS_EXPR 143 
#define  MIN_EXPR 142 
#define  MODIFY_EXPR 141 
#define  MULT_EXPR 140 
#define  NEGATE_EXPR 139 
#define  NE_EXPR 138 
#define  NOP_EXPR 137 
#define  PLUS_EXPR 136 
 scalar_t__ POINTER_TYPE ; 
#define  POSTDECREMENT_EXPR 135 
#define  POSTINCREMENT_EXPR 134 
#define  PREDECREMENT_EXPR 133 
#define  PREINCREMENT_EXPR 132 
 scalar_t__ REFERENCE_TYPE ; 
#define  RSHIFT_EXPR 131 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TRUNC_DIV_EXPR 130 
#define  TRUNC_MOD_EXPR 129 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_CLASS_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PTROB_P (scalar_t__) ; 
 scalar_t__ TYPE_PTR_P (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PTR_TO_MEMBER_P (scalar_t__) ; 
#define  UNARY_PLUS_EXPR 128 
 int /*<<< orphan*/  build_builtin_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ build_reference_type (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  is_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_ptr_cst_p (scalar_t__) ; 
 int /*<<< orphan*/  promoted_arithmetic_type_p (scalar_t__) ; 
 scalar_t__ ptrdiff_type_node ; 
 int /*<<< orphan*/  same_type_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uses_template_parms (scalar_t__) ; 

__attribute__((used)) static void
add_builtin_candidate (struct z_candidate **candidates, enum tree_code code,
		       enum tree_code code2, tree fnname, tree type1,
		       tree type2, tree *args, tree *argtypes, int flags)
{
  switch (code)
    {
    case POSTINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
      args[1] = integer_zero_node;
      type2 = integer_type_node;
      break;
    default:
      break;
    }

  switch (code)
    {

/* 4 For every pair T, VQ), where T is an arithmetic or  enumeration  type,
     and  VQ  is  either  volatile or empty, there exist candidate operator
     functions of the form
	     VQ T&   operator++(VQ T&);
	     T       operator++(VQ T&, int);
   5 For every pair T, VQ), where T is an enumeration type or an arithmetic
     type  other than bool, and VQ is either volatile or empty, there exist
     candidate operator functions of the form
	     VQ T&   operator--(VQ T&);
	     T       operator--(VQ T&, int);
   6 For every pair T, VQ), where T is  a  cv-qualified  or  cv-unqualified
     complete  object type, and VQ is either volatile or empty, there exist
     candidate operator functions of the form
	     T*VQ&   operator++(T*VQ&);
	     T*VQ&   operator--(T*VQ&);
	     T*      operator++(T*VQ&, int);
	     T*      operator--(T*VQ&, int);  */

    case POSTDECREMENT_EXPR:
    case PREDECREMENT_EXPR:
      if (TREE_CODE (type1) == BOOLEAN_TYPE)
	return;
    case POSTINCREMENT_EXPR:
    case PREINCREMENT_EXPR:
      if (ARITHMETIC_TYPE_P (type1) || TYPE_PTROB_P (type1))
	{
	  type1 = build_reference_type (type1);
	  break;
	}
      return;

/* 7 For every cv-qualified or cv-unqualified complete object type T, there
     exist candidate operator functions of the form

	     T&      operator*(T*);

   8 For every function type T, there exist candidate operator functions of
     the form
	     T&      operator*(T*);  */

    case INDIRECT_REF:
      if (TREE_CODE (type1) == POINTER_TYPE
	  && (TYPE_PTROB_P (type1)
	      || TREE_CODE (TREE_TYPE (type1)) == FUNCTION_TYPE))
	break;
      return;

/* 9 For every type T, there exist candidate operator functions of the form
	     T*      operator+(T*);

   10For  every  promoted arithmetic type T, there exist candidate operator
     functions of the form
	     T       operator+(T);
	     T       operator-(T);  */

    case UNARY_PLUS_EXPR: /* unary + */
      if (TREE_CODE (type1) == POINTER_TYPE)
	break;
    case NEGATE_EXPR:
      if (ARITHMETIC_TYPE_P (type1))
	break;
      return;

/* 11For every promoted integral type T,  there  exist  candidate  operator
     functions of the form
	     T       operator~(T);  */

    case BIT_NOT_EXPR:
      if (INTEGRAL_TYPE_P (type1))
	break;
      return;

/* 12For every quintuple C1, C2, T, CV1, CV2), where C2 is a class type, C1
     is the same type as C2 or is a derived class of C2, T  is  a  complete
     object type or a function type, and CV1 and CV2 are cv-qualifier-seqs,
     there exist candidate operator functions of the form
	     CV12 T& operator->*(CV1 C1*, CV2 T C2::*);
     where CV12 is the union of CV1 and CV2.  */

    case MEMBER_REF:
      if (TREE_CODE (type1) == POINTER_TYPE
	  && TYPE_PTR_TO_MEMBER_P (type2))
	{
	  tree c1 = TREE_TYPE (type1);
	  tree c2 = TYPE_PTRMEM_CLASS_TYPE (type2);

	  if (IS_AGGR_TYPE (c1) && DERIVED_FROM_P (c2, c1)
	      && (TYPE_PTRMEMFUNC_P (type2)
		  || is_complete (TYPE_PTRMEM_POINTED_TO_TYPE (type2))))
	    break;
	}
      return;

/* 13For every pair of promoted arithmetic types L and R, there exist  can-
     didate operator functions of the form
	     LR      operator*(L, R);
	     LR      operator/(L, R);
	     LR      operator+(L, R);
	     LR      operator-(L, R);
	     bool    operator<(L, R);
	     bool    operator>(L, R);
	     bool    operator<=(L, R);
	     bool    operator>=(L, R);
	     bool    operator==(L, R);
	     bool    operator!=(L, R);
     where  LR  is  the  result of the usual arithmetic conversions between
     types L and R.

   14For every pair of types T and I, where T  is  a  cv-qualified  or  cv-
     unqualified  complete  object  type and I is a promoted integral type,
     there exist candidate operator functions of the form
	     T*      operator+(T*, I);
	     T&      operator[](T*, I);
	     T*      operator-(T*, I);
	     T*      operator+(I, T*);
	     T&      operator[](I, T*);

   15For every T, where T is a pointer to complete object type, there exist
     candidate operator functions of the form112)
	     ptrdiff_t operator-(T, T);

   16For every pointer or enumeration type T, there exist candidate operator
     functions of the form
	     bool    operator<(T, T);
	     bool    operator>(T, T);
	     bool    operator<=(T, T);
	     bool    operator>=(T, T);
	     bool    operator==(T, T);
	     bool    operator!=(T, T);

   17For every pointer to member type T,  there  exist  candidate  operator
     functions of the form
	     bool    operator==(T, T);
	     bool    operator!=(T, T);  */

    case MINUS_EXPR:
      if (TYPE_PTROB_P (type1) && TYPE_PTROB_P (type2))
	break;
      if (TYPE_PTROB_P (type1) && INTEGRAL_TYPE_P (type2))
	{
	  type2 = ptrdiff_type_node;
	  break;
	}
    case MULT_EXPR:
    case TRUNC_DIV_EXPR:
      if (ARITHMETIC_TYPE_P (type1) && ARITHMETIC_TYPE_P (type2))
	break;
      return;

    case EQ_EXPR:
    case NE_EXPR:
      if ((TYPE_PTRMEMFUNC_P (type1) && TYPE_PTRMEMFUNC_P (type2))
	  || (TYPE_PTRMEM_P (type1) && TYPE_PTRMEM_P (type2)))
	break;
      if (TYPE_PTR_TO_MEMBER_P (type1) && null_ptr_cst_p (args[1]))
	{
	  type2 = type1;
	  break;
	}
      if (TYPE_PTR_TO_MEMBER_P (type2) && null_ptr_cst_p (args[0]))
	{
	  type1 = type2;
	  break;
	}
      /* Fall through.  */
    case LT_EXPR:
    case GT_EXPR:
    case LE_EXPR:
    case GE_EXPR:
    case MAX_EXPR:
    case MIN_EXPR:
      if (ARITHMETIC_TYPE_P (type1) && ARITHMETIC_TYPE_P (type2))
	break;
      if (TYPE_PTR_P (type1) && TYPE_PTR_P (type2))
	break;
      if (TREE_CODE (type1) == ENUMERAL_TYPE 
	  && TREE_CODE (type2) == ENUMERAL_TYPE)
	break;
      if (TYPE_PTR_P (type1) 
	  && null_ptr_cst_p (args[1])
	  && !uses_template_parms (type1))
	{
	  type2 = type1;
	  break;
	}
      if (null_ptr_cst_p (args[0]) 
	  && TYPE_PTR_P (type2)
	  && !uses_template_parms (type2))
	{
	  type1 = type2;
	  break;
	}
      return;

    case PLUS_EXPR:
      if (ARITHMETIC_TYPE_P (type1) && ARITHMETIC_TYPE_P (type2))
	break;
    case ARRAY_REF:
      if (INTEGRAL_TYPE_P (type1) && TYPE_PTROB_P (type2))
	{
	  type1 = ptrdiff_type_node;
	  break;
	}
      if (TYPE_PTROB_P (type1) && INTEGRAL_TYPE_P (type2))
	{
	  type2 = ptrdiff_type_node;
	  break;
	}
      return;

/* 18For  every pair of promoted integral types L and R, there exist candi-
     date operator functions of the form
	     LR      operator%(L, R);
	     LR      operator&(L, R);
	     LR      operator^(L, R);
	     LR      operator|(L, R);
	     L       operator<<(L, R);
	     L       operator>>(L, R);
     where LR is the result of the  usual  arithmetic  conversions  between
     types L and R.  */

    case TRUNC_MOD_EXPR:
    case BIT_AND_EXPR:
    case BIT_IOR_EXPR:
    case BIT_XOR_EXPR:
    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
      if (INTEGRAL_TYPE_P (type1) && INTEGRAL_TYPE_P (type2))
	break;
      return;

/* 19For  every  triple  L, VQ, R), where L is an arithmetic or enumeration
     type, VQ is either volatile or empty, and R is a  promoted  arithmetic
     type, there exist candidate operator functions of the form
	     VQ L&   operator=(VQ L&, R);
	     VQ L&   operator*=(VQ L&, R);
	     VQ L&   operator/=(VQ L&, R);
	     VQ L&   operator+=(VQ L&, R);
	     VQ L&   operator-=(VQ L&, R);

   20For  every  pair T, VQ), where T is any type and VQ is either volatile
     or empty, there exist candidate operator functions of the form
	     T*VQ&   operator=(T*VQ&, T*);

   21For every pair T, VQ), where T is a pointer to member type and  VQ  is
     either  volatile or empty, there exist candidate operator functions of
     the form
	     VQ T&   operator=(VQ T&, T);

   22For every triple  T,  VQ,  I),  where  T  is  a  cv-qualified  or  cv-
     unqualified  complete object type, VQ is either volatile or empty, and
     I is a promoted integral type, there exist  candidate  operator  func-
     tions of the form
	     T*VQ&   operator+=(T*VQ&, I);
	     T*VQ&   operator-=(T*VQ&, I);

   23For  every  triple  L,  VQ,  R), where L is an integral or enumeration
     type, VQ is either volatile or empty, and R  is  a  promoted  integral
     type, there exist candidate operator functions of the form

	     VQ L&   operator%=(VQ L&, R);
	     VQ L&   operator<<=(VQ L&, R);
	     VQ L&   operator>>=(VQ L&, R);
	     VQ L&   operator&=(VQ L&, R);
	     VQ L&   operator^=(VQ L&, R);
	     VQ L&   operator|=(VQ L&, R);  */

    case MODIFY_EXPR:
      switch (code2)
	{
	case PLUS_EXPR:
	case MINUS_EXPR:
	  if (TYPE_PTROB_P (type1) && INTEGRAL_TYPE_P (type2))
	    {
	      type2 = ptrdiff_type_node;
	      break;
	    }
	case MULT_EXPR:
	case TRUNC_DIV_EXPR:
	  if (ARITHMETIC_TYPE_P (type1) && ARITHMETIC_TYPE_P (type2))
	    break;
	  return;

	case TRUNC_MOD_EXPR:
	case BIT_AND_EXPR:
	case BIT_IOR_EXPR:
	case BIT_XOR_EXPR:
	case LSHIFT_EXPR:
	case RSHIFT_EXPR:
	  if (INTEGRAL_TYPE_P (type1) && INTEGRAL_TYPE_P (type2))
	    break;
	  return;

	case NOP_EXPR:
	  if (ARITHMETIC_TYPE_P (type1) && ARITHMETIC_TYPE_P (type2))
	    break;
	  if ((TYPE_PTRMEMFUNC_P (type1) && TYPE_PTRMEMFUNC_P (type2))
	      || (TYPE_PTR_P (type1) && TYPE_PTR_P (type2))
	      || (TYPE_PTRMEM_P (type1) && TYPE_PTRMEM_P (type2))
	      || ((TYPE_PTRMEMFUNC_P (type1)
		   || TREE_CODE (type1) == POINTER_TYPE)
		  && null_ptr_cst_p (args[1])))
	    {
	      type2 = type1;
	      break;
	    }
	  return;

	default:
	  gcc_unreachable ();
	}
      type1 = build_reference_type (type1);
      break;

    case COND_EXPR:
      /* [over.built]

	 For every pair of promoted arithmetic types L and R, there
	 exist candidate operator functions of the form

	 LR operator?(bool, L, R);

	 where LR is the result of the usual arithmetic conversions
	 between types L and R.

	 For every type T, where T is a pointer or pointer-to-member
	 type, there exist candidate operator functions of the form T
	 operator?(bool, T, T);  */

      if (promoted_arithmetic_type_p (type1)
	  && promoted_arithmetic_type_p (type2))
	/* That's OK.  */
	break;

      /* Otherwise, the types should be pointers.  */
      if (!(TYPE_PTR_P (type1) || TYPE_PTR_TO_MEMBER_P (type1))
	  || !(TYPE_PTR_P (type2) || TYPE_PTR_TO_MEMBER_P (type2)))
	return;

      /* We don't check that the two types are the same; the logic
	 below will actually create two candidates; one in which both
	 parameter types are TYPE1, and one in which both parameter
	 types are TYPE2.  */
      break;

    default:
      gcc_unreachable ();
    }

  /* If we're dealing with two pointer types or two enumeral types,
     we need candidates for both of them.  */
  if (type2 && !same_type_p (type1, type2)
      && TREE_CODE (type1) == TREE_CODE (type2)
      && (TREE_CODE (type1) == REFERENCE_TYPE
	  || (TYPE_PTR_P (type1) && TYPE_PTR_P (type2))
	  || (TYPE_PTRMEM_P (type1) && TYPE_PTRMEM_P (type2))
	  || TYPE_PTRMEMFUNC_P (type1)
	  || IS_AGGR_TYPE (type1)
	  || TREE_CODE (type1) == ENUMERAL_TYPE))
    {
      build_builtin_candidate
	(candidates, fnname, type1, type1, args, argtypes, flags);
      build_builtin_candidate
	(candidates, fnname, type2, type2, args, argtypes, flags);
      return;
    }

  build_builtin_candidate
    (candidates, fnname, type1, type2, args, argtypes, flags);
}