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
struct stab_demangle_info {unsigned int typestring_count; int /*<<< orphan*/  dhandle; int /*<<< orphan*/  info; TYPE_1__* typestrings; } ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  void* bfd_boolean ;
struct TYPE_2__ {char* typestring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KIND_CLASS ; 
 int /*<<< orphan*/ * DEBUG_TYPE_NULL ; 
 void* FALSE ; 
 int /*<<< orphan*/  ISDIGIT (char const) ; 
 void* TRUE ; 
 int /*<<< orphan*/ * debug_find_named_type (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * debug_make_array_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,void*) ; 
 int /*<<< orphan*/ * debug_make_const_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_function_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void*) ; 
 int /*<<< orphan*/ * debug_make_int_type (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/ * debug_make_method_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void*) ; 
 int /*<<< orphan*/ * debug_make_offset_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_pointer_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_reference_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stab_bad_demangle (char const*) ; 
 int /*<<< orphan*/  stab_demangle_args (struct stab_demangle_info*,char const**,int /*<<< orphan*/ ***,void**) ; 
 unsigned int stab_demangle_count (char const**) ; 
 int /*<<< orphan*/  stab_demangle_fund_type (struct stab_demangle_info*,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stab_demangle_get_count (char const**,unsigned int*) ; 
 int /*<<< orphan*/  stab_demangle_qualified (struct stab_demangle_info*,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * stab_find_tagged_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_type (struct stab_demangle_info *minfo, const char **pp,
		    debug_type *ptype)
{
  const char *orig;

  orig = *pp;

  switch (**pp)
    {
    case 'P':
    case 'p':
      /* A pointer type.  */
      ++*pp;
      if (! stab_demangle_type (minfo, pp, ptype))
	return FALSE;
      if (ptype != NULL)
	*ptype = debug_make_pointer_type (minfo->dhandle, *ptype);
      break;

    case 'R':
      /* A reference type.  */
      ++*pp;
      if (! stab_demangle_type (minfo, pp, ptype))
	return FALSE;
      if (ptype != NULL)
	*ptype = debug_make_reference_type (minfo->dhandle, *ptype);
      break;

    case 'A':
      /* An array.  */
      {
	unsigned long high;

	++*pp;
	high = 0;
	while (**pp != '\0' && **pp != '_')
	  {
	    if (! ISDIGIT (**pp))
	      {
		stab_bad_demangle (orig);
		return FALSE;
	      }
	    high *= 10;
	    high += **pp - '0';
	    ++*pp;
	  }
	if (**pp != '_')
	  {
	    stab_bad_demangle (orig);
	    return FALSE;
	  }
	++*pp;

	if (! stab_demangle_type (minfo, pp, ptype))
	  return FALSE;
	if (ptype != NULL)
	  {
	    debug_type int_type;

	    int_type = debug_find_named_type (minfo->dhandle, "int");
	    if (int_type == NULL)
	      int_type = debug_make_int_type (minfo->dhandle, 4, FALSE);
	    *ptype = debug_make_array_type (minfo->dhandle, *ptype, int_type,
					    0, high, FALSE);
	  }
      }
      break;

    case 'T':
      /* A back reference to a remembered type.  */
      {
	unsigned int i;
	const char *p;

	++*pp;
	if (! stab_demangle_get_count (pp, &i))
	  {
	    stab_bad_demangle (orig);
	    return FALSE;
	  }
	if (i >= minfo->typestring_count)
	  {
	    stab_bad_demangle (orig);
	    return FALSE;
	  }
	p = minfo->typestrings[i].typestring;
	if (! stab_demangle_type (minfo, &p, ptype))
	  return FALSE;
      }
      break;

    case 'F':
      /* A function.  */
      {
	debug_type *args;
	bfd_boolean varargs;

	++*pp;
	if (! stab_demangle_args (minfo, pp,
				  (ptype == NULL
				   ? (debug_type **) NULL
				   : &args),
				  (ptype == NULL
				   ? (bfd_boolean *) NULL
				   : &varargs)))
	  return FALSE;
	if (**pp != '_')
	  {
	    /* cplus_demangle will accept a function without a return
	       type, but I don't know when that will happen, or what
	       to do if it does.  */
	    stab_bad_demangle (orig);
	    return FALSE;
	  }
	++*pp;
	if (! stab_demangle_type (minfo, pp, ptype))
	  return FALSE;
	if (ptype != NULL)
	  *ptype = debug_make_function_type (minfo->dhandle, *ptype, args,
					     varargs);

      }
      break;

    case 'M':
    case 'O':
      {
	bfd_boolean memberp, constp, volatilep;
	debug_type class_type = DEBUG_TYPE_NULL;
	debug_type *args;
	bfd_boolean varargs;
	unsigned int n;
	const char *name;

	memberp = **pp == 'M';
	constp = FALSE;
	volatilep = FALSE;
	args = NULL;
	varargs = FALSE;

	++*pp;
	if (ISDIGIT (**pp))
	  {
	    n = stab_demangle_count (pp);
	    if (strlen (*pp) < n)
	      {
		stab_bad_demangle (orig);
		return FALSE;
	      }
	    name = *pp;
	    *pp += n;

	    if (ptype != NULL)
	      {
		class_type = stab_find_tagged_type (minfo->dhandle,
						    minfo->info,
						    name, (int) n,
						    DEBUG_KIND_CLASS);
		if (class_type == DEBUG_TYPE_NULL)
		  return FALSE;
	      }
	  }
	else if (**pp == 'Q')
	  {
	    if (! stab_demangle_qualified (minfo, pp,
					   (ptype == NULL
					    ? (debug_type *) NULL
					    : &class_type)))
	      return FALSE;
	  }
	else
	  {
	    stab_bad_demangle (orig);
	    return FALSE;
	  }

	if (memberp)
	  {
	    if (**pp == 'C')
	      {
		constp = TRUE;
		++*pp;
	      }
	    else if (**pp == 'V')
	      {
		volatilep = TRUE;
		++*pp;
	      }
	    if (**pp != 'F')
	      {
		stab_bad_demangle (orig);
		return FALSE;
	      }
	    ++*pp;
	    if (! stab_demangle_args (minfo, pp,
				      (ptype == NULL
				       ? (debug_type **) NULL
				       : &args),
				      (ptype == NULL
				       ? (bfd_boolean *) NULL
				       : &varargs)))
	      return FALSE;
	  }

	if (**pp != '_')
	  {
	    stab_bad_demangle (orig);
	    return FALSE;
	  }
	++*pp;

	if (! stab_demangle_type (minfo, pp, ptype))
	  return FALSE;

	if (ptype != NULL)
	  {
	    if (! memberp)
	      *ptype = debug_make_offset_type (minfo->dhandle, class_type,
					       *ptype);
	    else
	      {
		/* FIXME: We have no way to record constp or
                   volatilep.  */
		*ptype = debug_make_method_type (minfo->dhandle, *ptype,
						 class_type, args, varargs);
	      }
	  }
      }
      break;

    case 'G':
      ++*pp;
      if (! stab_demangle_type (minfo, pp, ptype))
	return FALSE;
      break;

    case 'C':
      ++*pp;
      if (! stab_demangle_type (minfo, pp, ptype))
	return FALSE;
      if (ptype != NULL)
	*ptype = debug_make_const_type (minfo->dhandle, *ptype);
      break;

    case 'Q':
      {
	const char *hold;

	hold = *pp;
	if (! stab_demangle_qualified (minfo, pp, ptype))
	  return FALSE;
      }
      break;

    default:
      if (! stab_demangle_fund_type (minfo, pp, ptype))
	return FALSE;
      break;
    }

  return TRUE;
}