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
struct stab_demangle_info {int /*<<< orphan*/  info; int /*<<< orphan*/  dhandle; } ;
typedef  scalar_t__ debug_type ;
typedef  scalar_t__ debug_field ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ const DEBUG_FIELD_NULL ; 
 int /*<<< orphan*/  DEBUG_KIND_CLASS ; 
 int /*<<< orphan*/  DEBUG_KIND_ILLEGAL ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ISDIGIT (char const) ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int atoi (char const*) ; 
 scalar_t__ debug_find_named_type (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ debug_get_field_type (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__* debug_get_fields (int /*<<< orphan*/ ,scalar_t__) ; 
 char* debug_get_type_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* savestring (char const*,unsigned int) ; 
 int /*<<< orphan*/  stab_bad_demangle (char const*) ; 
 unsigned int stab_demangle_count (char const**) ; 
 int /*<<< orphan*/  stab_demangle_template (struct stab_demangle_info*,char const**,char**) ; 
 scalar_t__ stab_find_tagged_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_qualified (struct stab_demangle_info *minfo, const char **pp,
			 debug_type *ptype)
{
  const char *orig;
  const char *p;
  unsigned int qualifiers;
  debug_type context;

  orig = *pp;

  switch ((*pp)[1])
    {
    case '_':
      /* GNU mangled name with more than 9 classes.  The count is
	 preceded by an underscore (to distinguish it from the <= 9
	 case) and followed by an underscore.  */
      p = *pp + 2;
      if (! ISDIGIT (*p) || *p == '0')
	{
	  stab_bad_demangle (orig);
	  return FALSE;
	}
      qualifiers = atoi (p);
      while (ISDIGIT (*p))
	++p;
      if (*p != '_')
	{
	  stab_bad_demangle (orig);
	  return FALSE;
	}
      *pp = p + 1;
      break;

    case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      qualifiers = (*pp)[1] - '0';
      /* Skip an optional underscore after the count.  */
      if ((*pp)[2] == '_')
	++*pp;
      *pp += 2;
      break;

    case '0':
    default:
      stab_bad_demangle (orig);
      return FALSE;
    }

  context = DEBUG_TYPE_NULL;

  /* Pick off the names.  */
  while (qualifiers-- > 0)
    {
      if (**pp == '_')
	++*pp;
      if (**pp == 't')
	{
	  char *name;

	  if (! stab_demangle_template (minfo, pp,
					ptype != NULL ? &name : NULL))
	    return FALSE;

	  if (ptype != NULL)
	    {
	      context = stab_find_tagged_type (minfo->dhandle, minfo->info,
					       name, strlen (name),
					       DEBUG_KIND_CLASS);
	      free (name);
	      if (context == DEBUG_TYPE_NULL)
		return FALSE;
	    }
	}
      else
	{
	  unsigned int len;

	  len = stab_demangle_count (pp);
	  if (strlen (*pp) < len)
	    {
	      stab_bad_demangle (orig);
	      return FALSE;
	    }

	  if (ptype != NULL)
	    {
	      const debug_field *fields;

	      fields = NULL;
	      if (context != DEBUG_TYPE_NULL)
		fields = debug_get_fields (minfo->dhandle, context);

	      context = DEBUG_TYPE_NULL;

	      if (fields != NULL)
		{
		  char *name;

		  /* Try to find the type by looking through the
                     fields of context until we find a field with the
                     same type.  This ought to work for a class
                     defined within a class, but it won't work for,
                     e.g., an enum defined within a class.  stabs does
                     not give us enough information to figure out the
                     latter case.  */

		  name = savestring (*pp, len);

		  for (; *fields != DEBUG_FIELD_NULL; fields++)
		    {
		      debug_type ft;
		      const char *dn;

		      ft = debug_get_field_type (minfo->dhandle, *fields);
		      if (ft == NULL)
			return FALSE;
		      dn = debug_get_type_name (minfo->dhandle, ft);
		      if (dn != NULL && strcmp (dn, name) == 0)
			{
			  context = ft;
			  break;
			}
		    }

		  free (name);
		}

	      if (context == DEBUG_TYPE_NULL)
		{
		  /* We have to fall back on finding the type by name.
                     If there are more types to come, then this must
                     be a class.  Otherwise, it could be anything.  */

		  if (qualifiers == 0)
		    {
		      char *name;

		      name = savestring (*pp, len);
		      context = debug_find_named_type (minfo->dhandle,
						       name);
		      free (name);
		    }

		  if (context == DEBUG_TYPE_NULL)
		    {
		      context = stab_find_tagged_type (minfo->dhandle,
						       minfo->info,
						       *pp, len,
						       (qualifiers == 0
							? DEBUG_KIND_ILLEGAL
							: DEBUG_KIND_CLASS));
		      if (context == DEBUG_TYPE_NULL)
			return FALSE;
		    }
		}
	    }

	  *pp += len;
	}
    }

  if (ptype != NULL)
    *ptype = context;

  return TRUE;
}