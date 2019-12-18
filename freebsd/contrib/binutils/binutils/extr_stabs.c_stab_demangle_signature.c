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
struct stab_demangle_info {int /*<<< orphan*/  varargs; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  stab_bad_demangle (char const*) ; 
 int /*<<< orphan*/  stab_demangle_args (struct stab_demangle_info*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stab_demangle_class (struct stab_demangle_info*,char const**,char const**) ; 
 int /*<<< orphan*/  stab_demangle_qualified (struct stab_demangle_info*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stab_demangle_remember_type (struct stab_demangle_info*,char const*,int) ; 
 int /*<<< orphan*/  stab_demangle_template (struct stab_demangle_info*,char const**,char**) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_signature (struct stab_demangle_info *minfo, const char **pp)
{
  const char *orig;
  bfd_boolean expect_func, func_done;
  const char *hold;

  orig = *pp;

  expect_func = FALSE;
  func_done = FALSE;
  hold = NULL;

  while (**pp != '\0')
    {
      switch (**pp)
	{
	case 'Q':
	  hold = *pp;
	  if (! stab_demangle_qualified (minfo, pp, (debug_type *) NULL)
	      || ! stab_demangle_remember_type (minfo, hold, *pp - hold))
	    return FALSE;
	  expect_func = TRUE;
	  hold = NULL;
	  break;

	case 'S':
	  /* Static member function.  FIXME: Can this happen?  */
	  if (hold == NULL)
	    hold = *pp;
	  ++*pp;
	  break;

	case 'C':
	  /* Const member function.  */
	  if (hold == NULL)
	    hold = *pp;
	  ++*pp;
	  break;

	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	  if (hold == NULL)
	    hold = *pp;
	  if (! stab_demangle_class (minfo, pp, (const char **) NULL)
	      || ! stab_demangle_remember_type (minfo, hold, *pp - hold))
	    return FALSE;
	  expect_func = TRUE;
	  hold = NULL;
	  break;

	case 'F':
	  /* Function.  I don't know if this actually happens with g++
             output.  */
	  hold = NULL;
	  func_done = TRUE;
	  ++*pp;
	  if (! stab_demangle_args (minfo, pp, &minfo->args, &minfo->varargs))
	    return FALSE;
	  break;

	case 't':
	  /* Template.  */
	  if (hold == NULL)
	    hold = *pp;
	  if (! stab_demangle_template (minfo, pp, (char **) NULL)
	      || ! stab_demangle_remember_type (minfo, hold, *pp - hold))
	    return FALSE;
	  hold = NULL;
	  expect_func = TRUE;
	  break;

	case '_':
	  /* At the outermost level, we cannot have a return type
	     specified, so if we run into another '_' at this point we
	     are dealing with a mangled name that is either bogus, or
	     has been mangled by some algorithm we don't know how to
	     deal with.  So just reject the entire demangling.  */
	  stab_bad_demangle (orig);
	  return FALSE;

	default:
	  /* Assume we have stumbled onto the first outermost function
	     argument token, and start processing args.  */
	  func_done = TRUE;
	  if (! stab_demangle_args (minfo, pp, &minfo->args, &minfo->varargs))
	    return FALSE;
	  break;
	}

      if (expect_func)
	{
	  func_done = TRUE;
	  if (! stab_demangle_args (minfo, pp, &minfo->args, &minfo->varargs))
	    return FALSE;
	}
    }

  if (! func_done)
    {
      /* With GNU style demangling, bar__3foo is 'foo::bar(void)', and
	 bar__3fooi is 'foo::bar(int)'.  We get here when we find the
	 first case, and need to ensure that the '(void)' gets added
	 to the current declp.  */
      if (! stab_demangle_args (minfo, pp, &minfo->args, &minfo->varargs))
	return FALSE;
    }

  return TRUE;
}