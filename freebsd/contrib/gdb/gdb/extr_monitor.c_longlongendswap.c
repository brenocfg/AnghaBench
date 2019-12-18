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

__attribute__((used)) static void
longlongendswap (unsigned char *a)
{
  int i, j;
  unsigned char x;
  i = 0;
  j = 7;
  while (i < 4)
    {
      x = *(a + i);
      *(a + i) = *(a + j);
      *(a + j) = x;
      i++, j--;
    }
}