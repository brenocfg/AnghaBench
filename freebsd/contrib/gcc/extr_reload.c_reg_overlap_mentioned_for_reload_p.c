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
 scalar_t__ CC0 ; 
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_RTX_CLASS (scalar_t__) ; 
 scalar_t__ MEM ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PC ; 
 scalar_t__ PLUS ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ RTX_AUTOINC ; 
 scalar_t__ SCRATCH ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int** hard_regno_nregs ; 
 int refers_to_mem_for_reload_p (int /*<<< orphan*/ ) ; 
 int refers_to_regno_for_reload_p (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* reg_equiv_constant ; 
 scalar_t__* reg_equiv_memory_loc ; 
 int reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ subreg_regno_offset (int,size_t,int /*<<< orphan*/ ,size_t) ; 

int
reg_overlap_mentioned_for_reload_p (rtx x, rtx in)
{
  int regno, endregno;

  /* Overly conservative.  */
  if (GET_CODE (x) == STRICT_LOW_PART
      || GET_RTX_CLASS (GET_CODE (x)) == RTX_AUTOINC)
    x = XEXP (x, 0);

  /* If either argument is a constant, then modifying X can not affect IN.  */
  if (CONSTANT_P (x) || CONSTANT_P (in))
    return 0;
  else if (GET_CODE (x) == SUBREG && GET_CODE (SUBREG_REG (x)) == MEM)
    return refers_to_mem_for_reload_p (in);
  else if (GET_CODE (x) == SUBREG)
    {
      regno = REGNO (SUBREG_REG (x));
      if (regno < FIRST_PSEUDO_REGISTER)
	regno += subreg_regno_offset (REGNO (SUBREG_REG (x)),
				      GET_MODE (SUBREG_REG (x)),
				      SUBREG_BYTE (x),
				      GET_MODE (x));
    }
  else if (REG_P (x))
    {
      regno = REGNO (x);

      /* If this is a pseudo, it must not have been assigned a hard register.
	 Therefore, it must either be in memory or be a constant.  */

      if (regno >= FIRST_PSEUDO_REGISTER)
	{
	  if (reg_equiv_memory_loc[regno])
	    return refers_to_mem_for_reload_p (in);
	  gcc_assert (reg_equiv_constant[regno]);
	  return 0;
	}
    }
  else if (MEM_P (x))
    return refers_to_mem_for_reload_p (in);
  else if (GET_CODE (x) == SCRATCH || GET_CODE (x) == PC
	   || GET_CODE (x) == CC0)
    return reg_mentioned_p (x, in);
  else 
    {
      gcc_assert (GET_CODE (x) == PLUS);

      /* We actually want to know if X is mentioned somewhere inside IN.
	 We must not say that (plus (sp) (const_int 124)) is in
	 (plus (sp) (const_int 64)), since that can lead to incorrect reload
	 allocation when spuriously changing a RELOAD_FOR_OUTPUT_ADDRESS
	 into a RELOAD_OTHER on behalf of another RELOAD_OTHER.  */
      while (MEM_P (in))
	in = XEXP (in, 0);
      if (REG_P (in))
	return 0;
      else if (GET_CODE (in) == PLUS)
	return (rtx_equal_p (x, in)
		|| reg_overlap_mentioned_for_reload_p (x, XEXP (in, 0))
		|| reg_overlap_mentioned_for_reload_p (x, XEXP (in, 1)));
      else return (reg_overlap_mentioned_for_reload_p (XEXP (x, 0), in)
		   || reg_overlap_mentioned_for_reload_p (XEXP (x, 1), in));
    }

  endregno = regno + (regno < FIRST_PSEUDO_REGISTER
		      ? hard_regno_nregs[regno][GET_MODE (x)] : 1);

  return refers_to_regno_for_reload_p (regno, endregno, in, (rtx*) 0);
}