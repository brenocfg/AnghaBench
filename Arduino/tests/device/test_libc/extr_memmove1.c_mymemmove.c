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

void
mymemmove (unsigned char *dest, unsigned char *src, size_t n)
{
  if ((src <= dest && src + n <= dest)
      || src >= dest)
    while (n-- > 0)
      *dest++ = *src++;
  else
    {
      dest += n;
      src += n;
      while (n-- > 0)
	*--dest = *--src;
    }
}