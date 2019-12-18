#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elt_loc_list {int /*<<< orphan*/  loc; struct elt_loc_list* next; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {struct elt_loc_list* locs; } ;
typedef  TYPE_1__ cselib_val ;

/* Variables and functions */
 int ADDRESS ; 
#define  AND 146 
#define  CONST 145 
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ ) ; 
 int CONST_INT ; 
 TYPE_1__* CSELIB_VAL_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIND_BASE_TERM (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
#define  HIGH 144 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 143 
#define  LO_SUM 142 
#define  MINUS 141 
#define  PLUS 140 
#define  POST_DEC 139 
#define  POST_INC 138 
#define  POST_MODIFY 137 
#define  PRE_DEC 136 
#define  PRE_INC 135 
#define  PRE_MODIFY 134 
 int /*<<< orphan*/  Pmode ; 
#define  REG 133 
 int /*<<< orphan*/  REG_BASE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_POINTER (int /*<<< orphan*/ ) ; 
#define  SIGN_EXTEND 132 
#define  SYMBOL_REF 131 
#define  TRUNCATE 130 
#define  VALUE 129 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
#define  ZERO_EXTEND 128 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 

rtx
find_base_term (rtx x)
{
  cselib_val *val;
  struct elt_loc_list *l;

#if defined (FIND_BASE_TERM)
  /* Try machine-dependent ways to find the base term.  */
  x = FIND_BASE_TERM (x);
#endif

  switch (GET_CODE (x))
    {
    case REG:
      return REG_BASE_VALUE (x);

    case TRUNCATE:
      if (GET_MODE_SIZE (GET_MODE (x)) < GET_MODE_SIZE (Pmode))
	return 0;
      /* Fall through.  */
    case HIGH:
    case PRE_INC:
    case PRE_DEC:
    case POST_INC:
    case POST_DEC:
    case PRE_MODIFY:
    case POST_MODIFY:
      return find_base_term (XEXP (x, 0));

    case ZERO_EXTEND:
    case SIGN_EXTEND:	/* Used for Alpha/NT pointers */
      {
	rtx temp = find_base_term (XEXP (x, 0));

	if (temp != 0 && CONSTANT_P (temp))
	  temp = convert_memory_address (Pmode, temp);

	return temp;
      }

    case VALUE:
      val = CSELIB_VAL_PTR (x);
      if (!val)
	return 0;
      for (l = val->locs; l; l = l->next)
	if ((x = find_base_term (l->loc)) != 0)
	  return x;
      return 0;

    case CONST:
      x = XEXP (x, 0);
      if (GET_CODE (x) != PLUS && GET_CODE (x) != MINUS)
	return 0;
      /* Fall through.  */
    case LO_SUM:
    case PLUS:
    case MINUS:
      {
	rtx tmp1 = XEXP (x, 0);
	rtx tmp2 = XEXP (x, 1);

	/* This is a little bit tricky since we have to determine which of
	   the two operands represents the real base address.  Otherwise this
	   routine may return the index register instead of the base register.

	   That may cause us to believe no aliasing was possible, when in
	   fact aliasing is possible.

	   We use a few simple tests to guess the base register.  Additional
	   tests can certainly be added.  For example, if one of the operands
	   is a shift or multiply, then it must be the index register and the
	   other operand is the base register.  */

	if (tmp1 == pic_offset_table_rtx && CONSTANT_P (tmp2))
	  return find_base_term (tmp2);

	/* If either operand is known to be a pointer, then use it
	   to determine the base term.  */
	if (REG_P (tmp1) && REG_POINTER (tmp1))
	  return find_base_term (tmp1);

	if (REG_P (tmp2) && REG_POINTER (tmp2))
	  return find_base_term (tmp2);

	/* Neither operand was known to be a pointer.  Go ahead and find the
	   base term for both operands.  */
	tmp1 = find_base_term (tmp1);
	tmp2 = find_base_term (tmp2);

	/* If either base term is named object or a special address
	   (like an argument or stack reference), then use it for the
	   base term.  */
	if (tmp1 != 0
	    && (GET_CODE (tmp1) == SYMBOL_REF
		|| GET_CODE (tmp1) == LABEL_REF
		|| (GET_CODE (tmp1) == ADDRESS
		    && GET_MODE (tmp1) != VOIDmode)))
	  return tmp1;

	if (tmp2 != 0
	    && (GET_CODE (tmp2) == SYMBOL_REF
		|| GET_CODE (tmp2) == LABEL_REF
		|| (GET_CODE (tmp2) == ADDRESS
		    && GET_MODE (tmp2) != VOIDmode)))
	  return tmp2;

	/* We could not determine which of the two operands was the
	   base register and which was the index.  So we can determine
	   nothing from the base alias check.  */
	return 0;
      }

    case AND:
      if (GET_CODE (XEXP (x, 1)) == CONST_INT && INTVAL (XEXP (x, 1)) != 0)
	return find_base_term (XEXP (x, 0));
      return 0;

    case SYMBOL_REF:
    case LABEL_REF:
      return x;

    default:
      return 0;
    }
}