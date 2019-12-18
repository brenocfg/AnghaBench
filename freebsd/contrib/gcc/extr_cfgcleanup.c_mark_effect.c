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
typedef  int /*<<< orphan*/  regset ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_REGNO_REG_SET (int /*<<< orphan*/ ,int) ; 
#define  CLOBBER 129 
 int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
#define  SET 128 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  pc_rtx ; 
 int /*<<< orphan*/  rtx_equal_for_cselib_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mark_effect (rtx exp, regset nonequal)
{
  int regno;
  rtx dest;
  switch (GET_CODE (exp))
    {
      /* In case we do clobber the register, mark it as equal, as we know the
	 value is dead so it don't have to match.  */
    case CLOBBER:
      if (REG_P (XEXP (exp, 0)))
	{
	  dest = XEXP (exp, 0);
	  regno = REGNO (dest);
	  CLEAR_REGNO_REG_SET (nonequal, regno);
	  if (regno < FIRST_PSEUDO_REGISTER)
	    {
	      int n = hard_regno_nregs[regno][GET_MODE (dest)];
	      while (--n > 0)
		CLEAR_REGNO_REG_SET (nonequal, regno + n);
	    }
	}
      return false;

    case SET:
      if (rtx_equal_for_cselib_p (SET_DEST (exp), SET_SRC (exp)))
	return false;
      dest = SET_DEST (exp);
      if (dest == pc_rtx)
	return false;
      if (!REG_P (dest))
	return true;
      regno = REGNO (dest);
      SET_REGNO_REG_SET (nonequal, regno);
      if (regno < FIRST_PSEUDO_REGISTER)
	{
	  int n = hard_regno_nregs[regno][GET_MODE (dest)];
	  while (--n > 0)
	    SET_REGNO_REG_SET (nonequal, regno + n);
	}
      return false;

    default:
      return false;
    }
}