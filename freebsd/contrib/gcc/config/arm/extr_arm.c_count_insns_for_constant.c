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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */

__attribute__((used)) static int
count_insns_for_constant (HOST_WIDE_INT remainder, int i)
{
  HOST_WIDE_INT temp1;
  int num_insns = 0;
  do
    {
      int end;

      if (i <= 0)
	i += 32;
      if (remainder & (3 << (i - 2)))
	{
	  end = i - 8;
	  if (end < 0)
	    end += 32;
	  temp1 = remainder & ((0x0ff << end)
				    | ((i < end) ? (0xff >> (32 - end)) : 0));
	  remainder &= ~temp1;
	  num_insns++;
	  i -= 6;
	}
      i -= 2;
    } while (remainder);
  return num_insns;
}