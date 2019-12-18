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
struct ieee_vars {struct ieee_var* vars; scalar_t__ alloc; } ;
struct ieee_var {unsigned long namlen; char const* name; scalar_t__* pslot; int /*<<< orphan*/  kind; } ;
struct ieee_tag {char const* name; scalar_t__* fslots; int /*<<< orphan*/  type; struct ieee_tag* next; } ;
struct ieee_info {int /*<<< orphan*/  dhandle; struct ieee_tag* tags; struct ieee_vars* global_vars; struct ieee_vars vars; } ;
typedef  scalar_t__ debug_type ;
typedef  scalar_t__ debug_field ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ const DEBUG_FIELD_NULL ; 
 scalar_t__ DEBUG_KIND_POINTER ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IEEE_EXTERNAL ; 
 int /*<<< orphan*/  IEEE_FUNCTION ; 
 int /*<<< orphan*/  IEEE_GLOBAL ; 
 int /*<<< orphan*/  IEEE_LOCAL ; 
 int /*<<< orphan*/  IEEE_STATIC ; 
 scalar_t__ TRUE ; 
 char* _ (char*) ; 
 char* debug_get_field_name (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__* debug_get_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_get_target_type (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ debug_get_type_kind (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ debug_make_reference_type (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ieee_error (struct ieee_info*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  ieee_require_asn (struct ieee_info*,int /*<<< orphan*/  const**,int*) ; 
 int /*<<< orphan*/  ieee_require_atn65 (struct ieee_info*,int /*<<< orphan*/  const**,char const**,unsigned long*) ; 
 unsigned long strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,unsigned long) ; 

__attribute__((used)) static bfd_boolean
ieee_read_reference (struct ieee_info *info, const bfd_byte **pp)
{
  const bfd_byte *start;
  bfd_vma flags;
  const char *class, *name;
  unsigned long classlen, namlen;
  debug_type *pslot;
  debug_type target;

  start = *pp;

  if (! ieee_require_asn (info, pp, &flags))
    return FALSE;

  /* Giving the class name before the member name is in an addendum to
     the spec.  */
  if (flags == 3)
    {
      if (! ieee_require_atn65 (info, pp, &class, &classlen))
	return FALSE;
    }

  if (! ieee_require_atn65 (info, pp, &name, &namlen))
    return FALSE;

  pslot = NULL;
  if (flags != 3)
    {
      int pass;

      /* We search from the last variable indices to the first in
	 hopes of finding local variables correctly.  We search the
	 local variables on the first pass, and the global variables
	 on the second.  FIXME: This probably won't work in all cases.
	 On the other hand, I don't know what will.  */
      for (pass = 0; pass < 2; pass++)
	{
	  struct ieee_vars *vars;
	  int i;
	  struct ieee_var *pv = NULL;

	  if (pass == 0)
	    vars = &info->vars;
	  else
	    {
	      vars = info->global_vars;
	      if (vars == NULL)
		break;
	    }

	  for (i = (int) vars->alloc - 1; i >= 0; i--)
	    {
	      bfd_boolean found;

	      pv = vars->vars + i;

	      if (pv->pslot == NULL
		  || pv->namlen != namlen
		  || strncmp (pv->name, name, namlen) != 0)
		continue;

	      found = FALSE;
	      switch (flags)
		{
		default:
		  ieee_error (info, start,
			      _("unrecognized C++ reference type"));
		  return FALSE;

		case 0:
		  /* Global variable or function.  */
		  if (pv->kind == IEEE_GLOBAL
		      || pv->kind == IEEE_EXTERNAL
		      || pv->kind == IEEE_FUNCTION)
		    found = TRUE;
		  break;

		case 1:
		  /* Global static variable or function.  */
		  if (pv->kind == IEEE_STATIC
		      || pv->kind == IEEE_FUNCTION)
		    found = TRUE;
		  break;

		case 2:
		  /* Local variable.  */
		  if (pv->kind == IEEE_LOCAL)
		    found = TRUE;
		  break;
		}

	      if (found)
		break;
	    }

	  if (i >= 0)
	    {
	      pslot = pv->pslot;
	      break;
	    }
	}
    }
  else
    {
      struct ieee_tag *it;

      for (it = info->tags; it != NULL; it = it->next)
	{
	  if (it->name[0] == class[0]
	      && strncmp (it->name, class, classlen) == 0
	      && strlen (it->name) == classlen)
	    {
	      if (it->fslots != NULL)
		{
		  const debug_field *pf;
		  unsigned int findx;

		  pf = debug_get_fields (info->dhandle, it->type);
		  if (pf == NULL)
		    {
		      ieee_error (info, start,
				  "C++ reference in class with no fields");
		      return FALSE;
		    }

		  for (findx = 0; *pf != DEBUG_FIELD_NULL; pf++, findx++)
		    {
		      const char *fname;

		      fname = debug_get_field_name (info->dhandle, *pf);
		      if (fname == NULL)
			return FALSE;
		      if (strncmp (fname, name, namlen) == 0
			  && strlen (fname) == namlen)
			{
			  pslot = it->fslots + findx;
			  break;
			}
		    }
		}

	      break;
	    }
	}
    }

  if (pslot == NULL)
    {
      ieee_error (info, start, _("C++ reference not found"));
      return FALSE;
    }

  /* We allocated the type of the object as an indirect type pointing
     to *pslot, which we can now update to be a reference type.  */
  if (debug_get_type_kind (info->dhandle, *pslot) != DEBUG_KIND_POINTER)
    {
      ieee_error (info, start, _("C++ reference is not pointer"));
      return FALSE;
    }

  target = debug_get_target_type (info->dhandle, *pslot);
  *pslot = debug_make_reference_type (info->dhandle, target);
  if (*pslot == DEBUG_TYPE_NULL)
    return FALSE;

  return TRUE;
}