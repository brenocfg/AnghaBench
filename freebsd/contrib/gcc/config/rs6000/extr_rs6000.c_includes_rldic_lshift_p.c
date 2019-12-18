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
includes_rldic_lshift_p (rtx shiftop, rtx andop)
{
  if (GET_CODE (andop) == CONST_INT)
    {
      HOST_WIDE_INT c, lsb, shift_mask;

      c = INTVAL (andop);
      if (c == 0 || c == ~0)
	return 0;

      shift_mask = ~0;
      shift_mask <<= INTVAL (shiftop);

      /* Find the least significant one bit.  */
      lsb = c & -c;

      /* It must coincide with the LSB of the shift mask.  */
      if (-lsb != shift_mask)
	return 0;

      /* Invert to look for the next transition (if any).  */
      c = ~c;

      /* Remove the low group of ones (originally low group of zeros).  */
      c &= -lsb;

      /* Again find the lsb, and check we have all 1's above.  */
      lsb = c & -c;
      return c == -lsb;
    }
  else if (GET_CODE (andop) == CONST_DOUBLE
	   && (GET_MODE (andop) == VOIDmode || GET_MODE (andop) == DImode))
    {
      HOST_WIDE_INT low, high, lsb;
      HOST_WIDE_INT shift_mask_low, shift_mask_high;

      low = CONST_DOUBLE_LOW (andop);
      if (HOST_BITS_PER_WIDE_INT < 64)
	high = CONST_DOUBLE_HIGH (andop);

      if ((low == 0 && (HOST_BITS_PER_WIDE_INT >= 64 || high == 0))
	  || (low == ~0 && (HOST_BITS_PER_WIDE_INT >= 64 || high == ~0)))
	return 0;

      if (HOST_BITS_PER_WIDE_INT < 64 && low == 0)
	{
	  shift_mask_high = ~0;
	  if (INTVAL (shiftop) > 32)
	    shift_mask_high <<= INTVAL (shiftop) - 32;

	  lsb = high & -high;

	  if (-lsb != shift_mask_high || INTVAL (shiftop) < 32)
	    return 0;

	  high = ~high;
	  high &= -lsb;

	  lsb = high & -high;
	  return high == -lsb;
	}

      shift_mask_low = ~0;
      shift_mask_low <<= INTVAL (shiftop);

      lsb = low & -low;

      if (-lsb != shift_mask_low)
	return 0;

      if (HOST_BITS_PER_WIDE_INT < 64)
	high = ~high;
      low = ~low;
      low &= -lsb;

      if (HOST_BITS_PER_WIDE_INT < 64 && low == 0)
	{
	  lsb = high & -high;
	  return high == -lsb;
	}

      lsb = low & -low;
      return low == -lsb && (HOST_BITS_PER_WIDE_INT >= 64 || high == ~0);
    }
  else
    return 0;
}