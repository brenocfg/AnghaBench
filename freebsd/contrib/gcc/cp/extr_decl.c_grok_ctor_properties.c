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
typedef  char* tree ;

/* Variables and functions */
 int copy_fn_p (char*) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 

int
grok_ctor_properties (tree ctype, tree decl)
{
  int ctor_parm = copy_fn_p (decl);

  if (ctor_parm < 0)
    {
      /* [class.copy]

	 A declaration of a constructor for a class X is ill-formed if
	 its first parameter is of type (optionally cv-qualified) X
	 and either there are no other parameters or else all other
	 parameters have default arguments.

	 We *don't* complain about member template instantiations that
	 have this form, though; they can occur as we try to decide
	 what constructor to use during overload resolution.  Since
	 overload resolution will never prefer such a constructor to
	 the non-template copy constructor (which is either explicitly
	 or implicitly defined), there's no need to worry about their
	 existence.  Theoretically, they should never even be
	 instantiated, but that's hard to forestall.  */
      error ("invalid constructor; you probably meant %<%T (const %T&)%>",
		ctype, ctype);
      return 0;
    }

  return 1;
}