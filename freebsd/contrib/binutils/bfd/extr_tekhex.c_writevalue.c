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
typedef  int bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/ * digs ; 

__attribute__((used)) static void
writevalue (char **dst, bfd_vma value)
{
  char *p = *dst;
  int len;
  int shift;

  for (len = 8, shift = 28; shift; shift -= 4, len--)
    {
      if ((value >> shift) & 0xf)
	{
	  *p++ = len + '0';
	  while (len)
	    {
	      *p++ = digs[(value >> shift) & 0xf];
	      shift -= 4;
	      len--;
	    }
	  *dst = p;
	  return;

	}
    }
  *p++ = '1';
  *p++ = '0';
  *dst = p;
}