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
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_VTABLE_STRING ; 
 int ARM_VTABLE_STRLEN ; 
 int consume_count (char const**) ; 
 int /*<<< orphan*/  string_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  string_prepend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  string_prependn (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
arm_special (const char **mangled, string *declp)
{
  int n;
  int success = 1;
  const char *scan;

  if (strncmp (*mangled, ARM_VTABLE_STRING, ARM_VTABLE_STRLEN) == 0)
    {
      /* Found a ARM style virtual table, get past ARM_VTABLE_STRING
         and create the decl.  Note that we consume the entire mangled
	 input string, which means that demangle_signature has no work
	 to do.  */
      scan = *mangled + ARM_VTABLE_STRLEN;
      while (*scan != '\0')        /* first check it can be demangled */
        {
          n = consume_count (&scan);
          if (n == -1)
	    {
	      return (0);           /* no good */
	    }
          scan += n;
          if (scan[0] == '_' && scan[1] == '_')
	    {
	      scan += 2;
	    }
        }
      (*mangled) += ARM_VTABLE_STRLEN;
      while (**mangled != '\0')
	{
	  n = consume_count (mangled);
          if (n == -1
	      || n > (long) strlen (*mangled))
	    return 0;
	  string_prependn (declp, *mangled, n);
	  (*mangled) += n;
	  if ((*mangled)[0] == '_' && (*mangled)[1] == '_')
	    {
	      string_prepend (declp, "::");
	      (*mangled) += 2;
	    }
	}
      string_append (declp, " virtual table");
    }
  else
    {
      success = 0;
    }
  return (success);
}