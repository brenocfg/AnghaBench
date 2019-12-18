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
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  scalar_t__ debug_type ;
typedef  scalar_t__ debug_baseclass ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ DEBUG_BASECLASS_NULL ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 int DEBUG_VISIBILITY_PRIVATE ; 
 int DEBUG_VISIBILITY_PROTECTED ; 
 int DEBUG_VISIBILITY_PUBLIC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 scalar_t__ debug_make_baseclass (void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_number (char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_stab_type (void*,struct stab_handle*,char const*,char const**,scalar_t__**) ; 
 int /*<<< orphan*/  warn_stab (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (unsigned int) ; 

__attribute__((used)) static bfd_boolean
parse_stab_baseclasses (void *dhandle, struct stab_handle *info,
			const char **pp, debug_baseclass **retp)
{
  const char *orig;
  unsigned int c, i;
  debug_baseclass *classes;

  *retp = NULL;

  orig = *pp;

  if (**pp != '!')
    {
      /* No base classes.  */
      return TRUE;
    }
  ++*pp;

  c = (unsigned int) parse_number (pp, (bfd_boolean *) NULL);

  if (**pp != ',')
    {
      bad_stab (orig);
      return FALSE;
    }
  ++*pp;

  classes = (debug_baseclass *) xmalloc ((c + 1) * sizeof (**retp));

  for (i = 0; i < c; i++)
    {
      bfd_boolean virtual;
      enum debug_visibility visibility;
      bfd_vma bitpos;
      debug_type type;

      switch (**pp)
	{
	case '0':
	  virtual = FALSE;
	  break;
	case '1':
	  virtual = TRUE;
	  break;
	default:
	  warn_stab (orig, _("unknown virtual character for baseclass"));
	  virtual = FALSE;
	  break;
	}
      ++*pp;

      switch (**pp)
	{
	case '0':
	  visibility = DEBUG_VISIBILITY_PRIVATE;
	  break;
	case '1':
	  visibility = DEBUG_VISIBILITY_PROTECTED;
	  break;
	case '2':
	  visibility = DEBUG_VISIBILITY_PUBLIC;
	  break;
	default:
	  warn_stab (orig, _("unknown visibility character for baseclass"));
	  visibility = DEBUG_VISIBILITY_PUBLIC;
	  break;
	}
      ++*pp;

      /* The remaining value is the bit offset of the portion of the
	 object corresponding to this baseclass.  Always zero in the
	 absence of multiple inheritance.  */
      bitpos = parse_number (pp, (bfd_boolean *) NULL);
      if (**pp != ',')
	{
	  bad_stab (orig);
	  return FALSE;
	}
      ++*pp;

      type = parse_stab_type (dhandle, info, (const char *) NULL, pp,
			      (debug_type **) NULL);
      if (type == DEBUG_TYPE_NULL)
	return FALSE;

      classes[i] = debug_make_baseclass (dhandle, type, bitpos, virtual,
					 visibility);
      if (classes[i] == DEBUG_BASECLASS_NULL)
	return FALSE;

      if (**pp != ';')
	return FALSE;
      ++*pp;
    }

  classes[i] = DEBUG_BASECLASS_NULL;

  *retp = classes;

  return TRUE;
}