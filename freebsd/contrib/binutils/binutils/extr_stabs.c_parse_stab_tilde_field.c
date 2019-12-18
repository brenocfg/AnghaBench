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
struct stab_handle {int dummy; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 int /*<<< orphan*/  parse_stab_type (void*,struct stab_handle*,char const*,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_stab_type_number (char const**,int*) ; 

__attribute__((used)) static bfd_boolean
parse_stab_tilde_field (void *dhandle, struct stab_handle *info,
			const char **pp, const int *typenums,
			debug_type *retvptrbase, bfd_boolean *retownvptr)
{
  const char *orig;
  const char *hold;
  int vtypenums[2];

  *retvptrbase = DEBUG_TYPE_NULL;
  *retownvptr = FALSE;

  orig = *pp;

  /* If we are positioned at a ';', then skip it.  */
  if (**pp == ';')
    ++*pp;

  if (**pp != '~')
    return TRUE;

  ++*pp;

  if (**pp == '=' || **pp == '+' || **pp == '-')
    {
      /* Obsolete flags that used to indicate the presence of
	 constructors and/or destructors.  */
      ++*pp;
    }

  if (**pp != '%')
    return TRUE;

  ++*pp;

  hold = *pp;

  /* The next number is the type number of the base class (possibly
     our own class) which supplies the vtable for this class.  */
  if (! parse_stab_type_number (pp, vtypenums))
    return FALSE;

  if (vtypenums[0] == typenums[0]
      && vtypenums[1] == typenums[1])
    *retownvptr = TRUE;
  else
    {
      debug_type vtype;
      const char *p;

      *pp = hold;

      vtype = parse_stab_type (dhandle, info, (const char *) NULL, pp,
			       (debug_type **) NULL);
      for (p = *pp; *p != ';' && *p != '\0'; p++)
	;
      if (*p != ';')
	{
	  bad_stab (orig);
	  return FALSE;
	}

      *retvptrbase = vtype;

      *pp = p + 1;
    }

  return TRUE;
}