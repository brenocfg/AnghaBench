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
extract_MB (rtx op)
{
  int i;
  unsigned long val = INT_LOWPART (op);

  /* If the high bit is zero, the value is the first 1 bit we find
     from the left.  */
  if ((val & 0x80000000) == 0)
    {
      gcc_assert (val & 0xffffffff);

      i = 1;
      while (((val <<= 1) & 0x80000000) == 0)
	++i;
      return i;
    }

  /* If the high bit is set and the low bit is not, or the mask is all
     1's, the value is zero.  */
  if ((val & 1) == 0 || (val & 0xffffffff) == 0xffffffff)
    return 0;

  /* Otherwise we have a wrap-around mask.  Look for the first 0 bit
     from the right.  */
  i = 31;
  while (((val >>= 1) & 1) != 0)
    --i;

  return i;
}