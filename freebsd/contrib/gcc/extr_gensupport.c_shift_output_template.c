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
 scalar_t__ ISALPHA (char) ; 
 scalar_t__ ISDIGIT (unsigned char) ; 

__attribute__((used)) static char *
shift_output_template (char *dest, const char *src, int disp)
{
  while (*src)
    {
      char c = *src++;
      *dest++ = c;
      if (c == '%')
	{
	  c = *src++;
	  if (ISDIGIT ((unsigned char) c))
	    c += disp;
	  else if (ISALPHA (c))
	    {
	      *dest++ = c;
	      c = *src++ + disp;
	    }
	  *dest++ = c;
	}
    }

  return dest;
}