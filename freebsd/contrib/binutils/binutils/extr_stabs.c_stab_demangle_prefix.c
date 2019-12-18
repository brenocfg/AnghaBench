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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISDIGIT (char const) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stab_bad_demangle (char const*) ; 
 int /*<<< orphan*/  stab_demangle_function_name (struct stab_demangle_info*,char const**,char const*) ; 
 char* strchr (char const*,char) ; 
 unsigned int strspn (char const*,char*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_prefix (struct stab_demangle_info *minfo, const char **pp,
		      unsigned int physname_len)
{
  const char *scan;
  unsigned int i;

  /* cplus_demangle checks for global constructors and destructors,
     but we can't see them in mangled argument types.  */

  if (physname_len)
    scan = *pp + physname_len;
  else
    {
      /* Look for `__'.  */
      scan = *pp;
      do
	scan = strchr (scan, '_');
      while (scan != NULL && *++scan != '_');

      if (scan == NULL)
	{
	  stab_bad_demangle (*pp);
	  return FALSE;
	}

      --scan;

      /* We found `__'; move ahead to the last contiguous `__' pair.  */
      i = strspn (scan, "_");
      if (i > 2)
	scan += i - 2;
    }

  if (scan == *pp
      && (ISDIGIT (scan[2])
	  || scan[2] == 'Q'
	  || scan[2] == 't'))
    {
      /* This is a GNU style constructor name.  */
      *pp = scan + 2;
      return TRUE;
    }
  else if (scan == *pp
	   && ! ISDIGIT (scan[2])
	   && scan[2] != 't')
    {
      /* Look for the `__' that separates the prefix from the
         signature.  */
      while (*scan == '_')
	++scan;
      scan = strstr (scan, "__");
      if (scan == NULL || scan[2] == '\0')
	{
	  stab_bad_demangle (*pp);
	  return FALSE;
	}

      return stab_demangle_function_name (minfo, pp, scan);
    }
  else if (scan[2] != '\0')
    {
      /* The name doesn't start with `__', but it does contain `__'.  */
      return stab_demangle_function_name (minfo, pp, scan);
    }
  else
    {
      stab_bad_demangle (*pp);
      return FALSE;
    }
  /*NOTREACHED*/
}