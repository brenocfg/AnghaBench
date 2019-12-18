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
struct deps {unsigned int nvpaths; int* vpathlv; int /*<<< orphan*/ * vpathv; } ;

/* Variables and functions */
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const char *
apply_vpath (struct deps *d, const char *t)
{
  if (d->vpathv)
    {
      unsigned int i;
      for (i = 0; i < d->nvpaths; i++)
	{
	  if (!strncmp (d->vpathv[i], t, d->vpathlv[i]))
	    {
	      const char *p = t + d->vpathlv[i];
	      if (!IS_DIR_SEPARATOR (*p))
		goto not_this_one;

	      /* Do not simplify $(vpath)/../whatever.  ??? Might not
		 be necessary. */
	      if (p[1] == '.' && p[2] == '.' && IS_DIR_SEPARATOR (p[3]))
		goto not_this_one;

	      /* found a match */
	      t = t + d->vpathlv[i] + 1;
	      break;
	    }
	not_this_one:;
	}
    }

  /* Remove leading ./ in any case.  */
  while (t[0] == '.' && IS_DIR_SEPARATOR (t[1]))
    {
      t += 2;
      /* If we removed a leading ./, then also remove any /s after the
	 first.  */
      while (IS_DIR_SEPARATOR (t[0]))
	++t;
    }

  return t;
}