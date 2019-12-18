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
 scalar_t__ EXPR_LIST ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  LABEL_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  modified_between_p (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ reg_set_p (scalar_t__,scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ single_set (scalar_t__) ; 

rtx
find_last_value (rtx x, rtx *pinsn, rtx valid_to, int allow_hwreg)
{
  rtx p;

  for (p = PREV_INSN (*pinsn); p && !LABEL_P (p);
       p = PREV_INSN (p))
    if (INSN_P (p))
      {
	rtx set = single_set (p);
	rtx note = find_reg_note (p, REG_EQUAL, NULL_RTX);

	if (set && rtx_equal_p (x, SET_DEST (set)))
	  {
	    rtx src = SET_SRC (set);

	    if (note && GET_CODE (XEXP (note, 0)) != EXPR_LIST)
	      src = XEXP (note, 0);

	    if ((valid_to == NULL_RTX
		 || ! modified_between_p (src, PREV_INSN (p), valid_to))
		/* Reject hard registers because we don't usually want
		   to use them; we'd rather use a pseudo.  */
		&& (! (REG_P (src)
		      && REGNO (src) < FIRST_PSEUDO_REGISTER) || allow_hwreg))
	      {
		*pinsn = p;
		return src;
	      }
	  }

	/* If set in non-simple way, we don't have a value.  */
	if (reg_set_p (x, p))
	  break;
      }

  return x;
}