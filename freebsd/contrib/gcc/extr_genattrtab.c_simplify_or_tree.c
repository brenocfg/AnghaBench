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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ AND ; 
 scalar_t__ EQ_ATTR ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ IOR ; 
 scalar_t__ NOT ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XSTR (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ attr_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ attr_rtx (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ false_rtx ; 
 scalar_t__ simplify_test_exp_in_temp (scalar_t__,int,int) ; 
 scalar_t__ true_rtx ; 

__attribute__((used)) static rtx
simplify_or_tree (rtx exp, rtx *pterm, int insn_code, int insn_index)
{
  rtx left, right;
  rtx newexp;
  rtx temp;
  int left_eliminates_term, right_eliminates_term;

  if (GET_CODE (exp) == IOR)
    {
      left  = simplify_or_tree (XEXP (exp, 0), pterm, insn_code, insn_index);
      right = simplify_or_tree (XEXP (exp, 1), pterm, insn_code, insn_index);
      if (left != XEXP (exp, 0) || right != XEXP (exp, 1))
	{
	  newexp = attr_rtx (GET_CODE (exp), left, right);

	  exp = simplify_test_exp_in_temp (newexp, insn_code, insn_index);
	}
    }

  else if (GET_CODE (exp) == AND)
    {
      /* For the AND case, we do the same as above, except that we can
         only eliminate `term' if both sides of the AND would do so.  */
      temp = *pterm;
      left = simplify_or_tree (XEXP (exp, 0), &temp, insn_code, insn_index);
      left_eliminates_term = (temp == false_rtx);

      temp = *pterm;
      right = simplify_or_tree (XEXP (exp, 1), &temp, insn_code, insn_index);
      right_eliminates_term = (temp == false_rtx);

      if (left_eliminates_term && right_eliminates_term)
	*pterm = false_rtx;

      if (left != XEXP (exp, 0) || right != XEXP (exp, 1))
	{
	  newexp = attr_rtx (GET_CODE (exp), left, right);

	  exp = simplify_test_exp_in_temp (newexp, insn_code, insn_index);
	}
    }

  if (attr_equal_p (exp, *pterm))
    return false_rtx;

  else if (GET_CODE (exp) == NOT && attr_equal_p (XEXP (exp, 0), *pterm))
    return true_rtx;

  else if (GET_CODE (*pterm) == NOT && attr_equal_p (XEXP (*pterm, 0), exp))
    return true_rtx;

  else if (GET_CODE (*pterm) == EQ_ATTR && GET_CODE (exp) == NOT
	   && GET_CODE (XEXP (exp, 0)) == EQ_ATTR
	   && XSTR (*pterm, 0) == XSTR (XEXP (exp, 0), 0))
    *pterm = false_rtx;

  else if (GET_CODE (exp) == EQ_ATTR && GET_CODE (*pterm) == NOT
	   && GET_CODE (XEXP (*pterm, 0)) == EQ_ATTR
	   && XSTR (exp, 0) == XSTR (XEXP (*pterm, 0), 0))
    return false_rtx;

  return exp;
}