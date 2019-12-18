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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 

int
mems_ok_for_quad_peep (rtx mem1, rtx mem2)
{
  rtx addr1, addr2;
  unsigned int reg1, reg2;
  int offset1, offset2;

  /* The mems cannot be volatile.  */
  if (MEM_VOLATILE_P (mem1) || MEM_VOLATILE_P (mem2))
    return 0;

  addr1 = XEXP (mem1, 0);
  addr2 = XEXP (mem2, 0);

  /* Extract an offset (if used) from the first addr.  */
  if (GET_CODE (addr1) == PLUS)
    {
      /* If not a REG, return zero.  */
      if (GET_CODE (XEXP (addr1, 0)) != REG)
	return 0;
      else
	{
	  reg1 = REGNO (XEXP (addr1, 0));
	  /* The offset must be constant!  */
	  if (GET_CODE (XEXP (addr1, 1)) != CONST_INT)
	    return 0;
	  offset1 = INTVAL (XEXP (addr1, 1));
	}
    }
  else if (GET_CODE (addr1) != REG)
    return 0;
  else
    {
      reg1 = REGNO (addr1);
      /* This was a simple (mem (reg)) expression.  Offset is 0.  */
      offset1 = 0;
    }

  /* And now for the second addr.  */
  if (GET_CODE (addr2) == PLUS)
    {
      /* If not a REG, return zero.  */
      if (GET_CODE (XEXP (addr2, 0)) != REG)
	return 0;
      else
	{
	  reg2 = REGNO (XEXP (addr2, 0));
	  /* The offset must be constant. */
	  if (GET_CODE (XEXP (addr2, 1)) != CONST_INT)
	    return 0;
	  offset2 = INTVAL (XEXP (addr2, 1));
	}
    }
  else if (GET_CODE (addr2) != REG)
    return 0;
  else
    {
      reg2 = REGNO (addr2);
      /* This was a simple (mem (reg)) expression.  Offset is 0.  */
      offset2 = 0;
    }

  /* Both of these must have the same base register.  */
  if (reg1 != reg2)
    return 0;

  /* The offset for the second addr must be 8 more than the first addr.  */
  if (offset2 != offset1 + 8)
    return 0;

  /* All the tests passed.  addr1 and addr2 are valid for lfq or stfq
     instructions.  */
  return 1;
}