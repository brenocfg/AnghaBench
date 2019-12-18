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
unw_print_grmask (char *cp, unsigned int mask)
{
  int sep = 0;
  int i;

  for (i = 0; i < 4; ++i)
    {
      if (mask & 1)
	{
	  if (sep)
	    *cp++ = ',';
	  *cp++ = 'r';
	  *cp++ = i + 4 + '0';
	  sep = 1;
	}
      mask >>= 1;
    }
  *cp = '\0';
}