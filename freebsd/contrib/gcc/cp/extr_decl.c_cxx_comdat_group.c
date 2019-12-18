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
 int /*<<< orphan*/  CLASSTYPE_VTABLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ONE_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_THUNK_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_VTABLE_OR_VTT_P (int /*<<< orphan*/ ) ; 
 char const* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_USE_LOCAL_THUNK_ALIAS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THUNK_TARGET (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 

const char *
cxx_comdat_group (tree decl)
{
  tree name;

  /* Virtual tables, construction virtual tables, and virtual table
     tables all go in a single COMDAT group, named after the primary
     virtual table.  */
  if (TREE_CODE (decl) == VAR_DECL && DECL_VTABLE_OR_VTT_P (decl))
    name = DECL_ASSEMBLER_NAME (CLASSTYPE_VTABLES (DECL_CONTEXT (decl)));
  /* For all other DECLs, the COMDAT group is the mangled name of the
     declaration itself.  */
  else
    {
      while (DECL_THUNK_P (decl))
	{
	  /* If TARGET_USE_LOCAL_THUNK_ALIAS_P, use_thunk puts the thunk
	     into the same section as the target function.  In that case
	     we must return target's name.  */
	  tree target = THUNK_TARGET (decl);
	  if (TARGET_USE_LOCAL_THUNK_ALIAS_P (target)
	      && DECL_SECTION_NAME (target) != NULL
	      && DECL_ONE_ONLY (target))
	    decl = target;
	  else
	    break;
	}
      name = DECL_ASSEMBLER_NAME (decl);
    }

  return IDENTIFIER_POINTER (name);
}