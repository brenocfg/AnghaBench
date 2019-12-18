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
typedef  scalar_t__ debug_type ;
typedef  scalar_t__ debug_field ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ DEBUG_FIELD_NULL ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  DEBUG_VISIBILITY_PRIVATE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 char* concat (char*,char const*,char const*) ; 
 char* debug_get_type_name (void*,scalar_t__) ; 
 scalar_t__ debug_make_field (void*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_number (char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_stab_type (void*,struct stab_handle*,char const*,char const**,scalar_t__**) ; 
 int /*<<< orphan*/  warn_stab (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
parse_stab_cpp_abbrev (void *dhandle, struct stab_handle *info,
		       const char **pp, debug_field *retp)
{
  const char *orig;
  int cpp_abbrev;
  debug_type context;
  const char *name;
  const char *typename;
  debug_type type;
  bfd_vma bitpos;

  *retp = DEBUG_FIELD_NULL;

  orig = *pp;

  if (**pp != 'v')
    {
      bad_stab (*pp);
      return FALSE;
    }
  ++*pp;

  cpp_abbrev = **pp;
  ++*pp;

  /* At this point, *pp points to something like "22:23=*22...", where
     the type number before the ':' is the "context" and everything
     after is a regular type definition.  Lookup the type, find it's
     name, and construct the field name.  */

  context = parse_stab_type (dhandle, info, (const char *) NULL, pp,
			     (debug_type **) NULL);
  if (context == DEBUG_TYPE_NULL)
    return FALSE;

  switch (cpp_abbrev)
    {
    case 'f':
      /* $vf -- a virtual function table pointer.  */
      name = "_vptr$";
      break;
    case 'b':
      /* $vb -- a virtual bsomethingorother */
      typename = debug_get_type_name (dhandle, context);
      if (typename == NULL)
	{
	  warn_stab (orig, _("unnamed $vb type"));
	  typename = "FOO";
	}
      name = concat ("_vb$", typename, (const char *) NULL);
      break;
    default:
      warn_stab (orig, _("unrecognized C++ abbreviation"));
      name = "INVALID_CPLUSPLUS_ABBREV";
      break;
    }

  if (**pp != ':')
    {
      bad_stab (orig);
      return FALSE;
    }
  ++*pp;

  type = parse_stab_type (dhandle, info, (const char *) NULL, pp,
			  (debug_type **) NULL);
  if (**pp != ',')
    {
      bad_stab (orig);
      return FALSE;
    }
  ++*pp;

  bitpos = parse_number (pp, (bfd_boolean *) NULL);
  if (**pp != ';')
    {
      bad_stab (orig);
      return FALSE;
    }
  ++*pp;

  *retp = debug_make_field (dhandle, name, type, bitpos, 0,
			    DEBUG_VISIBILITY_PRIVATE);
  if (*retp == DEBUG_FIELD_NULL)
    return FALSE;

  return TRUE;
}