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

__attribute__((used)) static char *
skip_whitespace (char *p)
{
  while (1)
    {
      /* A fully-blank line is a delimiter in the SPEC file and shouldn't
	 be considered whitespace.  */
      if (p[0] == '\n' && p[1] == '\n' && p[2] == '\n')
	return p + 1;
      else if (*p == '\n' || *p == ' ' || *p == '\t')
	p++;
      else if (*p == '#')
	{
	  while (*p != '\n')
	    p++;
	  p++;
	}
      else
	break;
    }

  return p;
}