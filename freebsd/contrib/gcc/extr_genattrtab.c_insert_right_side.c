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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int AND ; 
 int GET_CODE (scalar_t__) ; 
 int IOR ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ attr_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ attr_rtx (int,scalar_t__,scalar_t__) ; 
 scalar_t__ false_rtx ; 
 scalar_t__ simplify_test_exp_in_temp (scalar_t__,int,int) ; 
 scalar_t__ true_rtx ; 

__attribute__((used)) static rtx
insert_right_side (enum rtx_code code, rtx exp, rtx term, int insn_code, int insn_index)
{
  rtx newexp;

  /* Avoid consing in some special cases.  */
  if (code == AND && term == true_rtx)
    return exp;
  if (code == AND && term == false_rtx)
    return false_rtx;
  if (code == AND && exp == true_rtx)
    return term;
  if (code == AND && exp == false_rtx)
    return false_rtx;
  if (code == IOR && term == true_rtx)
    return true_rtx;
  if (code == IOR && term == false_rtx)
    return exp;
  if (code == IOR && exp == true_rtx)
    return true_rtx;
  if (code == IOR && exp == false_rtx)
    return term;
  if (attr_equal_p (exp, term))
    return exp;

  if (GET_CODE (term) == code)
    {
      exp = insert_right_side (code, exp, XEXP (term, 0),
			       insn_code, insn_index);
      exp = insert_right_side (code, exp, XEXP (term, 1),
			       insn_code, insn_index);

      return exp;
    }

  if (GET_CODE (exp) == code)
    {
      rtx new = insert_right_side (code, XEXP (exp, 1),
				   term, insn_code, insn_index);
      if (new != XEXP (exp, 1))
	/* Make a copy of this expression and call recursively.  */
	newexp = attr_rtx (code, XEXP (exp, 0), new);
      else
	newexp = exp;
    }
  else
    {
      /* Insert the new term.  */
      newexp = attr_rtx (code, exp, term);
    }

  return simplify_test_exp_in_temp (newexp, insn_code, insn_index);
}