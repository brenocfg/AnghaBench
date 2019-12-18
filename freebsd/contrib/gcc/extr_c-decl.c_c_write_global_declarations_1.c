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
typedef  int TREE_NO_WARNING ;

/* Variables and functions */
 scalar_t__ C_DECL_USED (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PUBLIC (scalar_t__) ; 
 int /*<<< orphan*/  check_global_declaration_1 (scalar_t__) ; 
 int /*<<< orphan*/  pedwarn (char*,scalar_t__) ; 
 int /*<<< orphan*/  wrapup_global_declaration_1 (scalar_t__) ; 
 int wrapup_global_declaration_2 (scalar_t__) ; 

__attribute__((used)) static void
c_write_global_declarations_1 (tree globals)
{
  tree decl;
  bool reconsider;

  /* Process the decls in the order they were written.  */
  for (decl = globals; decl; decl = TREE_CHAIN (decl))
    {
      /* Check for used but undefined static functions using the C
	 standard's definition of "used", and set TREE_NO_WARNING so
	 that check_global_declarations doesn't repeat the check.  */
      if (TREE_CODE (decl) == FUNCTION_DECL
	  && DECL_INITIAL (decl) == 0
	  && DECL_EXTERNAL (decl)
	  && !TREE_PUBLIC (decl)
	  && C_DECL_USED (decl))
	{
	  pedwarn ("%q+F used but never defined", decl);
	  TREE_NO_WARNING (decl) = 1;
	}

      wrapup_global_declaration_1 (decl);
    }

  do
    {
      reconsider = false;
      for (decl = globals; decl; decl = TREE_CHAIN (decl))
	reconsider |= wrapup_global_declaration_2 (decl);
    }
  while (reconsider);

  for (decl = globals; decl; decl = TREE_CHAIN (decl))
    check_global_declaration_1 (decl);
}