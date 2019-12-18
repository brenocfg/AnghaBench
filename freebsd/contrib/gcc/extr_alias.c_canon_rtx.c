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
 scalar_t__ CONST_INT ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  INTVAL (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ PLUS ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ get_reg_known_value (scalar_t__) ; 
 scalar_t__ plus_constant (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ replace_equiv_address_nv (scalar_t__,scalar_t__) ; 

rtx
canon_rtx (rtx x)
{
  /* Recursively look for equivalences.  */
  if (REG_P (x) && REGNO (x) >= FIRST_PSEUDO_REGISTER)
    {
      rtx t = get_reg_known_value (REGNO (x));
      if (t == x)
	return x;
      if (t)
	return canon_rtx (t);
    }

  if (GET_CODE (x) == PLUS)
    {
      rtx x0 = canon_rtx (XEXP (x, 0));
      rtx x1 = canon_rtx (XEXP (x, 1));

      if (x0 != XEXP (x, 0) || x1 != XEXP (x, 1))
	{
	  if (GET_CODE (x0) == CONST_INT)
	    return plus_constant (x1, INTVAL (x0));
	  else if (GET_CODE (x1) == CONST_INT)
	    return plus_constant (x0, INTVAL (x1));
	  return gen_rtx_PLUS (GET_MODE (x), x0, x1);
	}
    }

  /* This gives us much better alias analysis when called from
     the loop optimizer.   Note we want to leave the original
     MEM alone, but need to return the canonicalized MEM with
     all the flags with their original values.  */
  else if (MEM_P (x))
    x = replace_equiv_address_nv (x, canon_rtx (XEXP (x, 0)));

  return x;
}