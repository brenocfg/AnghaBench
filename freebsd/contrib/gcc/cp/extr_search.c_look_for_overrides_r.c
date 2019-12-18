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
typedef  scalar_t__ tree ;
typedef  int DECL_VIRTUAL_P ;

/* Variables and functions */
 scalar_t__ DECL_STATIC_FUNCTION_P (scalar_t__) ; 
 int /*<<< orphan*/  check_final_overrider (int,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int look_for_overrides (scalar_t__,scalar_t__) ; 
 scalar_t__ look_for_overrides_here (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
look_for_overrides_r (tree type, tree fndecl)
{
  tree fn = look_for_overrides_here (type, fndecl);
  if (fn)
    {
      if (DECL_STATIC_FUNCTION_P (fndecl))
	{
	  /* A static member function cannot match an inherited
	     virtual member function.  */
	  error ("%q+#D cannot be declared", fndecl);
	  error ("  since %q+#D declared in base class", fn);
	}
      else
	{
	  /* It's definitely virtual, even if not explicitly set.  */
	  DECL_VIRTUAL_P (fndecl) = 1;
	  check_final_overrider (fndecl, fn);
	}
      return 1;
    }

  /* We failed to find one declared in this class. Look in its bases.  */
  return look_for_overrides (type, fndecl);
}