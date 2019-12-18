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

__attribute__((used)) static int
topower (int x)
{
  unsigned int i = 1;
  int l;

  if (x < 0)
    return -1;

  for (l = 0; l < 32; l++)
    {
      if (i >= (unsigned int) x)
	return l;
      i <<= 1;
    }

  return 0;
}