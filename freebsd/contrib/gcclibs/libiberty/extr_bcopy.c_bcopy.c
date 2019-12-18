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
bcopy (const void *src, void *dest, size_t len)
{
  if (dest < src)
    {
      const char *firsts = src;
      char *firstd = dest;
      while (len--)
	*firstd++ = *firsts++;
    }
  else
    {
      const char *lasts = (const char *)src + (len-1);
      char *lastd = (char *)dest + (len-1);
      while (len--)
        *lastd-- = *lasts--;
    }
}