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
typedef  int CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static unsigned long
calculate_mask (CORE_ADDR addr, int len)
{
  unsigned long mask;
  int i;

  mask = addr ^ (addr + len - 1);

  for (i = 32; i >= 0; i--)
    if (mask == 0)
      break;
    else
      mask >>= 1;

  mask = (unsigned long) 0xffffffff >> i;

  return mask;
}