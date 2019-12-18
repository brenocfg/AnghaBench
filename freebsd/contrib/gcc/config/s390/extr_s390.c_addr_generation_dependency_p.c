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
 scalar_t__ ATYPE_AGEN ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REG ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_LA ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_attr_atype (int /*<<< orphan*/ ) ; 
 int refers_to_regno_p (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_used_in_mem_p (int,int /*<<< orphan*/ ) ; 
 scalar_t__ s390_safe_attr_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
addr_generation_dependency_p (rtx dep_rtx, rtx insn)
{
  rtx target, pat;

  if (GET_CODE (dep_rtx) == INSN)
      dep_rtx = PATTERN (dep_rtx);

  if (GET_CODE (dep_rtx) == SET)
    {
      target = SET_DEST (dep_rtx);
      if (GET_CODE (target) == STRICT_LOW_PART)
	target = XEXP (target, 0);
      while (GET_CODE (target) == SUBREG)
	target = SUBREG_REG (target);

      if (GET_CODE (target) == REG)
	{
	  int regno = REGNO (target);

	  if (s390_safe_attr_type (insn) == TYPE_LA)
	    {
	      pat = PATTERN (insn);
	      if (GET_CODE (pat) == PARALLEL)
		{
		  gcc_assert (XVECLEN (pat, 0) == 2);
		  pat = XVECEXP (pat, 0, 0);
		}
	      gcc_assert (GET_CODE (pat) == SET);
	      return refers_to_regno_p (regno, regno+1, SET_SRC (pat), 0);
	    }
	  else if (get_attr_atype (insn) == ATYPE_AGEN)
	    return reg_used_in_mem_p (regno, PATTERN (insn));
	}
    }
  return false;
}