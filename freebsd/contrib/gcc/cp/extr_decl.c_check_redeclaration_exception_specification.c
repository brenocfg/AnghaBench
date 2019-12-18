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
 int /*<<< orphan*/  DECL_IN_SYSTEM_HEADER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_IS_BUILTIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_RAISES_EXCEPTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comp_except_specs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_exceptions ; 
 scalar_t__ pedantic ; 

__attribute__((used)) static void
check_redeclaration_exception_specification (tree new_decl,
					     tree old_decl)
{
  tree new_type;
  tree old_type;
  tree new_exceptions;
  tree old_exceptions;

  new_type = TREE_TYPE (new_decl);
  new_exceptions = TYPE_RAISES_EXCEPTIONS (new_type);
  old_type = TREE_TYPE (old_decl);
  old_exceptions = TYPE_RAISES_EXCEPTIONS (old_type);

  /* [except.spec]

     If any declaration of a function has an exception-specification,
     all declarations, including the definition and an explicit
     specialization, of that function shall have an
     exception-specification with the same set of type-ids.  */
  if ((pedantic || ! DECL_IN_SYSTEM_HEADER (old_decl))
      && ! DECL_IS_BUILTIN (old_decl)
      && flag_exceptions
      && !comp_except_specs (new_exceptions, old_exceptions,
			     /*exact=*/true))
    {
      error ("declaration of %qF throws different exceptions", new_decl);
      error ("from previous declaration %q+F", old_decl);
    }
}