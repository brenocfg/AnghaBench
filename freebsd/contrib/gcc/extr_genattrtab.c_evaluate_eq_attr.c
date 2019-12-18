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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  AND ; 
 int /*<<< orphan*/  ATTR_IND_SIMPLIFIED_P (int /*<<< orphan*/ ) ; 
#define  COND 130 
#define  CONST_STRING 129 
 int /*<<< orphan*/  DEF_ATTR_STRING (char*) ; 
 int /*<<< orphan*/  EQ ; 
 int EQ_ATTR ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOR ; 
 int const NOT ; 
#define  SYMBOL_REF 128 
 char TOUPPER (char) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ address_used ; 
 int /*<<< orphan*/  attr_rtx (int const,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  copy_rtx_unchanging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  false_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  insert_right_side (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  simplify_test_exp_in_temp (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp_check (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  true_rtx ; 
 int /*<<< orphan*/  walk_attr_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
evaluate_eq_attr (rtx exp, rtx value, int insn_code, int insn_index)
{
  rtx orexp, andexp;
  rtx right;
  rtx newexp;
  int i;

  switch (GET_CODE (value))
    {
    case CONST_STRING:
      if (! strcmp_check (XSTR (value, 0), XSTR (exp, 1)))
	newexp = true_rtx;
      else
	newexp = false_rtx;
      break;
      
    case SYMBOL_REF:
      {
	char *p;
	char string[256];
	
	gcc_assert (GET_CODE (exp) == EQ_ATTR);
	gcc_assert (strlen (XSTR (exp, 0)) + strlen (XSTR (exp, 1)) + 2
		    <= 256);
	
	strcpy (string, XSTR (exp, 0));
	strcat (string, "_");
	strcat (string, XSTR (exp, 1));
	for (p = string; *p; p++)
	  *p = TOUPPER (*p);
	
	newexp = attr_rtx (EQ, value,
			   attr_rtx (SYMBOL_REF,
				     DEF_ATTR_STRING (string)));
	break;
      }

    case COND:
      /* We construct an IOR of all the cases for which the
	 requested attribute value is present.  Since we start with
	 FALSE, if it is not present, FALSE will be returned.
	  
	 Each case is the AND of the NOT's of the previous conditions with the
	 current condition; in the default case the current condition is TRUE.
	  
	 For each possible COND value, call ourselves recursively.
	  
	 The extra TRUE and FALSE expressions will be eliminated by another
	 call to the simplification routine.  */

      orexp = false_rtx;
      andexp = true_rtx;

      for (i = 0; i < XVECLEN (value, 0); i += 2)
	{
	  rtx this = simplify_test_exp_in_temp (XVECEXP (value, 0, i),
						insn_code, insn_index);

	  right = insert_right_side (AND, andexp, this,
				     insn_code, insn_index);
	  right = insert_right_side (AND, right,
				     evaluate_eq_attr (exp,
						       XVECEXP (value, 0,
								i + 1),
						       insn_code, insn_index),
				     insn_code, insn_index);
	  orexp = insert_right_side (IOR, orexp, right,
				     insn_code, insn_index);

	  /* Add this condition into the AND expression.  */
	  newexp = attr_rtx (NOT, this);
	  andexp = insert_right_side (AND, andexp, newexp,
				      insn_code, insn_index);
	}

      /* Handle the default case.  */
      right = insert_right_side (AND, andexp,
				 evaluate_eq_attr (exp, XEXP (value, 1),
						   insn_code, insn_index),
				 insn_code, insn_index);
      newexp = insert_right_side (IOR, orexp, right, insn_code, insn_index);
      break;

    default:
      gcc_unreachable ();
    }

  /* If uses an address, must return original expression.  But set the
     ATTR_IND_SIMPLIFIED_P bit so we don't try to simplify it again.  */

  address_used = 0;
  walk_attr_value (newexp);

  if (address_used)
    {
      if (! ATTR_IND_SIMPLIFIED_P (exp))
	return copy_rtx_unchanging (exp);
      return exp;
    }
  else
    return newexp;
}