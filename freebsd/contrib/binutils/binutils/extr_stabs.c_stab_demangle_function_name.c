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
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stab_demangle_type (struct stab_demangle_info*,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_function_name (struct stab_demangle_info *minfo,
			     const char **pp, const char *scan)
{
  const char *name;

  /* The string from *pp to scan is the name of the function.  We
     don't care about the name, since we just looking for argument
     types.  However, for conversion operators, the name may include a
     type which we must remember in order to handle backreferences.  */

  name = *pp;
  *pp = scan + 2;

  if (*pp - name >= 5
	   && CONST_STRNEQ (name, "type")
	   && (name[4] == '$' || name[4] == '.'))
    {
      const char *tem;

      /* This is a type conversion operator.  */
      tem = name + 5;
      if (! stab_demangle_type (minfo, &tem, (debug_type *) NULL))
	return FALSE;
    }
  else if (name[0] == '_'
	   && name[1] == '_'
	   && name[2] == 'o'
	   && name[3] == 'p')
    {
      const char *tem;

      /* This is a type conversion operator.  */
      tem = name + 4;
      if (! stab_demangle_type (minfo, &tem, (debug_type *) NULL))
	return FALSE;
    }

  return TRUE;
}