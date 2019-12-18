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
 scalar_t__ CONST_DOUBLE ; 
 int CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 int CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 

int
includes_rldicr_lshift_p (rtx shiftop, rtx andop)
{
  if (GET_CODE (andop) == CONST_INT)
    {
      HOST_WIDE_INT c, lsb, shift_mask;

      shift_mask = ~0;
      shift_mask <<= INTVAL (shiftop);
      c = INTVAL (andop);

      /* Find the least significant one bit.  */
      lsb = c & -c;

      /* It must be covered by the shift mask.
	 This test also rejects c == 0.  */
      if ((lsb & shift_mask) == 0)
	return 0;

      /* Check we have all 1's above the transition, and reject all 1's.  */
      return c == -lsb && lsb != 1;
    }
  else if (GET_CODE (andop) == CONST_DOUBLE
	   && (GET_MODE (andop) == VOIDmode || GET_MODE (andop) == DImode))
    {
      HOST_WIDE_INT low, lsb, shift_mask_low;

      low = CONST_DOUBLE_LOW (andop);

      if (HOST_BITS_PER_WIDE_INT < 64)
	{
	  HOST_WIDE_INT high, shift_mask_high;

	  high = CONST_DOUBLE_HIGH (andop);

	  if (low == 0)
	    {
	      shift_mask_high = ~0;
	      if (INTVAL (shiftop) > 32)
		shift_mask_high <<= INTVAL (shiftop) - 32;

	      lsb = high & -high;

	      if ((lsb & shift_mask_high) == 0)
		return 0;

	      return high == -lsb;
	    }
	  if (high != ~0)
	    return 0;
	}

      shift_mask_low = ~0;
      shift_mask_low <<= INTVAL (shiftop);

      lsb = low & -low;

      if ((lsb & shift_mask_low) == 0)
	return 0;

      return low == -lsb && lsb != 1;
    }
  else
    return 0;
}