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
 int FILESYSTEM_PREFIX_LEN (char const*) ; 
 scalar_t__ ISSLASH (char const) ; 

char *
base_name (char const *name)
{
  char const *base = name + FILESYSTEM_PREFIX_LEN (name);
  char const *p;

  for (p = base; *p; p++)
    {
      if (ISSLASH (*p))
	{
	  /* Treat multiple adjacent slashes like a single slash.  */
	  do p++;
	  while (ISSLASH (*p));

	  /* If the file name ends in slash, use the trailing slash as
	     the basename if no non-slashes have been found.  */
	  if (! *p)
	    {
	      if (ISSLASH (*base))
		base = p - 1;
	      break;
	    }

	  /* *P is a non-slash preceded by a slash.  */
	  base = p;
	}
    }

  return (char *) base;
}