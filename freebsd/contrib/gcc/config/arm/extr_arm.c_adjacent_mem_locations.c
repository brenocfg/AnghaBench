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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ arm_eliminable_register (int /*<<< orphan*/ ) ; 
 scalar_t__ arm_ld_sched ; 
 int /*<<< orphan*/  const_ok_for_op (scalar_t__,int) ; 
 scalar_t__ optimize_size ; 
 scalar_t__ volatile_refs_p (int /*<<< orphan*/ ) ; 

int
adjacent_mem_locations (rtx a, rtx b)
{
  /* We don't guarantee to preserve the order of these memory refs.  */
  if (volatile_refs_p (a) || volatile_refs_p (b))
    return 0;

  if ((GET_CODE (XEXP (a, 0)) == REG
       || (GET_CODE (XEXP (a, 0)) == PLUS
	   && GET_CODE (XEXP (XEXP (a, 0), 1)) == CONST_INT))
      && (GET_CODE (XEXP (b, 0)) == REG
	  || (GET_CODE (XEXP (b, 0)) == PLUS
	      && GET_CODE (XEXP (XEXP (b, 0), 1)) == CONST_INT)))
    {
      HOST_WIDE_INT val0 = 0, val1 = 0;
      rtx reg0, reg1;
      int val_diff;

      if (GET_CODE (XEXP (a, 0)) == PLUS)
        {
	  reg0 = XEXP (XEXP (a, 0), 0);
	  val0 = INTVAL (XEXP (XEXP (a, 0), 1));
        }
      else
	reg0 = XEXP (a, 0);

      if (GET_CODE (XEXP (b, 0)) == PLUS)
        {
	  reg1 = XEXP (XEXP (b, 0), 0);
	  val1 = INTVAL (XEXP (XEXP (b, 0), 1));
        }
      else
	reg1 = XEXP (b, 0);

      /* Don't accept any offset that will require multiple
	 instructions to handle, since this would cause the
	 arith_adjacentmem pattern to output an overlong sequence.  */
      if (!const_ok_for_op (PLUS, val0) || !const_ok_for_op (PLUS, val1))
	return 0;

      /* Don't allow an eliminable register: register elimination can make
	 the offset too large.  */
      if (arm_eliminable_register (reg0))
	return 0;

      val_diff = val1 - val0;

      if (arm_ld_sched)
	{
	  /* If the target has load delay slots, then there's no benefit
	     to using an ldm instruction unless the offset is zero and
	     we are optimizing for size.  */
	  return (optimize_size && (REGNO (reg0) == REGNO (reg1))
		  && (val0 == 0 || val1 == 0 || val0 == 4 || val1 == 4)
		  && (val_diff == 4 || val_diff == -4));
	}

      return ((REGNO (reg0) == REGNO (reg1))
	      && (val_diff == 4 || val_diff == -4));
    }

  return 0;
}