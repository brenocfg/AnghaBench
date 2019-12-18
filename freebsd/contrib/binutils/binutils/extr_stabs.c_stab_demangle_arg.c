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
struct stab_demangle_info {int dummy; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stab_demangle_remember_type (struct stab_demangle_info*,char const*,int) ; 
 int /*<<< orphan*/  stab_demangle_type (struct stab_demangle_info*,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ xrealloc (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_arg (struct stab_demangle_info *minfo, const char **pp,
		   debug_type **pargs, unsigned int *pcount,
		   unsigned int *palloc)
{
  const char *start;
  debug_type type;

  start = *pp;
  if (! stab_demangle_type (minfo, pp,
			    pargs == NULL ? (debug_type *) NULL : &type)
      || ! stab_demangle_remember_type (minfo, start, *pp - start))
    return FALSE;

  if (pargs != NULL)
    {
      if (type == DEBUG_TYPE_NULL)
	return FALSE;

      if (*pcount + 1 >= *palloc)
	{
	  *palloc += 10;
	  *pargs = ((debug_type *)
		    xrealloc (*pargs, *palloc * sizeof **pargs));
	}
      (*pargs)[*pcount] = type;
      ++*pcount;
    }

  return TRUE;
}