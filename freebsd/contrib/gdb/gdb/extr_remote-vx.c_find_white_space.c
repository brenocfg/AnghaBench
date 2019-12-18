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
find_white_space (char *p)
{
  int c;

  while ((c = *p) != ' ' && c != '\t' && c)
    {
      if (c == '\'' || c == '"')
	{
	  while (*++p != c && *p)
	    {
	      if (*p == '\\')
		p++;
	    }
	  if (!*p)
	    break;
	}
      p++;
    }
  return p;
}