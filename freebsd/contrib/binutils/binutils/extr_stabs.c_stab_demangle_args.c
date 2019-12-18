#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stab_demangle_info {unsigned int typestring_count; TYPE_1__* typestrings; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {char* typestring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stab_bad_demangle (char const*) ; 
 int /*<<< orphan*/  stab_demangle_arg (struct stab_demangle_info*,char const**,int /*<<< orphan*/ **,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stab_demangle_get_count (char const**,unsigned int*) ; 
 scalar_t__ xmalloc (unsigned int) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_args (struct stab_demangle_info *minfo, const char **pp,
		    debug_type **pargs, bfd_boolean *pvarargs)
{
  const char *orig;
  unsigned int alloc, count;

  orig = *pp;

  alloc = 10;
  if (pargs != NULL)
    {
      *pargs = (debug_type *) xmalloc (alloc * sizeof **pargs);
      *pvarargs = FALSE;
    }
  count = 0;

  while (**pp != '_' && **pp != '\0' && **pp != 'e')
    {
      if (**pp == 'N' || **pp == 'T')
	{
	  char temptype;
	  unsigned int r, t;

	  temptype = **pp;
	  ++*pp;

	  if (temptype == 'T')
	    r = 1;
	  else
	    {
	      if (! stab_demangle_get_count (pp, &r))
		{
		  stab_bad_demangle (orig);
		  return FALSE;
		}
	    }

	  if (! stab_demangle_get_count (pp, &t))
	    {
	      stab_bad_demangle (orig);
	      return FALSE;
	    }

	  if (t >= minfo->typestring_count)
	    {
	      stab_bad_demangle (orig);
	      return FALSE;
	    }
	  while (r-- > 0)
	    {
	      const char *tem;

	      tem = minfo->typestrings[t].typestring;
	      if (! stab_demangle_arg (minfo, &tem, pargs, &count, &alloc))
		return FALSE;
	    }
	}
      else
	{
	  if (! stab_demangle_arg (minfo, pp, pargs, &count, &alloc))
	    return FALSE;
	}
    }

  if (pargs != NULL)
    (*pargs)[count] = DEBUG_TYPE_NULL;

  if (**pp == 'e')
    {
      if (pargs != NULL)
	*pvarargs = TRUE;
      ++*pp;
    }

  return TRUE;
}