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
 unsigned long INT_LOWPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (unsigned long) ; 

int
extract_ME (rtx op)
{
  int i;
  unsigned long val = INT_LOWPART (op);

  /* If the low bit is zero, the value is the first 1 bit we find from
     the right.  */
  if ((val & 1) == 0)
    {
      gcc_assert (val & 0xffffffff);

      i = 30;
      while (((val >>= 1) & 1) == 0)
	--i;

      return i;
    }

  /* If the low bit is set and the high bit is not, or the mask is all
     1's, the value is 31.  */
  if ((val & 0x80000000) == 0 || (val & 0xffffffff) == 0xffffffff)
    return 31;

  /* Otherwise we have a wrap-around mask.  Look for the first 0 bit
     from the left.  */
  i = 0;
  while (((val <<= 1) & 0x80000000) != 0)
    ++i;

  return i;
}