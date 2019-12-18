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
 scalar_t__ EQ_ATTR_ALT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ IOR ; 
 scalar_t__ NOT ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XSTR (scalar_t__,int) ; 
 scalar_t__ attr_alt_subset_of_compl_p (scalar_t__,scalar_t__) ; 
 scalar_t__ attr_alt_subset_p (scalar_t__,scalar_t__) ; 
 scalar_t__ attr_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ attr_rtx (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ false_rtx ; 
 scalar_t__ simplify_test_exp_in_temp (scalar_t__,int,int) ; 
 int /*<<< orphan*/  strcmp_check (scalar_t__,scalar_t__) ; 
 scalar_t__ true_rtx ; 

__attribute__((used)) static rtx
simplify_and_tree (rtx exp, rtx *pterm, int insn_code, int insn_index)
{
  rtx left, right;
  rtx newexp;
  rtx temp;
  int left_eliminates_term, right_eliminates_term;

  if (GET_CODE (exp) == AND)
    {
      left  = simplify_and_tree (XEXP (exp, 0), pterm, insn_code, insn_index);
      right = simplify_and_tree (XEXP (exp, 1), pterm, insn_code, insn_index);
      if (left != XEXP (exp, 0) || right != XEXP (exp, 1))
	{
	  newexp = attr_rtx (AND, left, right);

	  exp = simplify_test_exp_in_temp (newexp, insn_code, insn_index);
	}
    }

  else if (GET_CODE (exp) == IOR)
    {
      /* For the IOR case, we do the same as above, except that we can
         only eliminate `term' if both sides of the IOR would do so.  */
      temp = *pterm;
      left = simplify_and_tree (XEXP (exp, 0), &temp, insn_code, insn_index);
      left_eliminates_term = (temp == true_rtx);

      temp = *pterm;
      right = simplify_and_tree (XEXP (exp, 1), &temp, insn_code, insn_index);
      right_eliminates_term = (temp == true_rtx);

      if (left_eliminates_term && right_eliminates_term)
	*pterm = true_rtx;

      if (left != XEXP (exp, 0) || right != XEXP (exp, 1))
	{
	  newexp = attr_rtx (IOR, left, right);

	  exp = simplify_test_exp_in_temp (newexp, insn_code, insn_index);
	}
    }

  /* Check for simplifications.  Do some extra checking here since this
     routine is called so many times.  */

  if (exp == *pterm)
    return true_rtx;

  else if (GET_CODE (exp) == NOT && XEXP (exp, 0) == *pterm)
    return false_rtx;

  else if (GET_CODE (*pterm) == NOT && exp == XEXP (*pterm, 0))
    return false_rtx;

  else if (GET_CODE (exp) == EQ_ATTR_ALT && GET_CODE (*pterm) == EQ_ATTR_ALT)
    {
      if (attr_alt_subset_p (*pterm, exp))
	return true_rtx;

      if (attr_alt_subset_of_compl_p (*pterm, exp))
	return false_rtx;

      if (attr_alt_subset_p (exp, *pterm))
	*pterm = true_rtx;
	
      return exp;
    }

  else if (GET_CODE (exp) == EQ_ATTR && GET_CODE (*pterm) == EQ_ATTR)
    {
      if (XSTR (exp, 0) != XSTR (*pterm, 0))
	return exp;

      if (! strcmp_check (XSTR (exp, 1), XSTR (*pterm, 1)))
	return true_rtx;
      else
	return false_rtx;
    }

  else if (GET_CODE (*pterm) == EQ_ATTR && GET_CODE (exp) == NOT
	   && GET_CODE (XEXP (exp, 0)) == EQ_ATTR)
    {
      if (XSTR (*pterm, 0) != XSTR (XEXP (exp, 0), 0))
	return exp;

      if (! strcmp_check (XSTR (*pterm, 1), XSTR (XEXP (exp, 0), 1)))
	return false_rtx;
      else
	return true_rtx;
    }

  else if (GET_CODE (exp) == EQ_ATTR && GET_CODE (*pterm) == NOT
	   && GET_CODE (XEXP (*pterm, 0)) == EQ_ATTR)
    {
      if (XSTR (exp, 0) != XSTR (XEXP (*pterm, 0), 0))
	return exp;

      if (! strcmp_check (XSTR (exp, 1), XSTR (XEXP (*pterm, 0), 1)))
	return false_rtx;
      else
	*pterm = true_rtx;
    }

  else if (GET_CODE (exp) == NOT && GET_CODE (*pterm) == NOT)
    {
      if (attr_equal_p (XEXP (exp, 0), XEXP (*pterm, 0)))
	return true_rtx;
    }

  else if (GET_CODE (exp) == NOT)
    {
      if (attr_equal_p (XEXP (exp, 0), *pterm))
	return false_rtx;
    }

  else if (GET_CODE (*pterm) == NOT)
    {
      if (attr_equal_p (XEXP (*pterm, 0), exp))
	return false_rtx;
    }

  else if (attr_equal_p (exp, *pterm))
    return true_rtx;

  return exp;
}