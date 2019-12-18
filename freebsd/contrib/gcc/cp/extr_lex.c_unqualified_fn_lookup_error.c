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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  flag_permissive ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  unqualified_name_lookup_error (int /*<<< orphan*/ ) ; 

tree
unqualified_fn_lookup_error (tree name)
{
  if (processing_template_decl)
    {
      /* In a template, it is invalid to write "f()" or "f(3)" if no
	 declaration of "f" is available.  Historically, G++ and most
	 other compilers accepted that usage since they deferred all name
	 lookup until instantiation time rather than doing unqualified
	 name lookup at template definition time; explain to the user what
	 is going wrong.

	 Note that we have the exact wording of the following message in
	 the manual (trouble.texi, node "Name lookup"), so they need to
	 be kept in synch.  */
      pedwarn ("there are no arguments to %qD that depend on a template "
	       "parameter, so a declaration of %qD must be available",
	       name, name);

      if (!flag_permissive)
	{
	  static bool hint;
	  if (!hint)
	    {
	      error ("(if you use %<-fpermissive%>, G++ will accept your "
		     "code, but allowing the use of an undeclared name is "
		     "deprecated)");
	      hint = true;
	    }
	}
      return name;
    }

  return unqualified_name_lookup_error (name);
}