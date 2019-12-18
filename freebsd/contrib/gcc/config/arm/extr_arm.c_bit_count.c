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

/* Variables and functions */

__attribute__((used)) static unsigned
bit_count (unsigned long value)
{
  unsigned long count = 0;

  while (value)
    {
      count++;
      value &= value - 1;  /* Clear the least-significant set bit.  */
    }

  return count;
}