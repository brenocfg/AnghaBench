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
typedef  int /*<<< orphan*/  lin ;

/* Variables and functions */
 scalar_t__ memcmp (char* const,char*,size_t const) ; 

__attribute__((used)) static bool
copy_stringlist (char * const fromptrs[], size_t const fromlengths[],
		 char *toptrs[], size_t tolengths[],
		 lin copynum)
{
  register char * const *f = fromptrs;
  register char **t = toptrs;
  register size_t const *fl = fromlengths;
  register size_t *tl = tolengths;

  while (copynum--)
    {
      if (*t)
	{
	  if (*fl != *tl || memcmp (*f, *t, *fl) != 0)
	    return false;
	}
      else
	{
	  *t = *f;
	  *tl = *fl;
	}

      t++; f++; tl++; fl++;
    }

  return true;
}