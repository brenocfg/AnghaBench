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
 int /*<<< orphan*/  ASM_FORMAT_PRIVATE_NAME (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SET_DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 

void
lhd_set_decl_assembler_name (tree decl)
{
  /* The language-independent code should never use the
     DECL_ASSEMBLER_NAME for lots of DECLs.  Only FUNCTION_DECLs and
     VAR_DECLs for variables with static storage duration need a real
     DECL_ASSEMBLER_NAME.  */
  gcc_assert (TREE_CODE (decl) == FUNCTION_DECL
	      || (TREE_CODE (decl) == VAR_DECL
		  && (TREE_STATIC (decl)
		      || DECL_EXTERNAL (decl)
		      || TREE_PUBLIC (decl))));
  
  /* By default, assume the name to use in assembly code is the same
     as that used in the source language.  (That's correct for C, and
     GCC used to set DECL_ASSEMBLER_NAME to the same value as
     DECL_NAME in build_decl, so this choice provides backwards
     compatibility with existing front-ends.
      
     Can't use just the variable's own name for a variable whose scope
     is less than the whole compilation.  Concatenate a distinguishing
     number - we use the DECL_UID.  */
  if (TREE_PUBLIC (decl) || DECL_CONTEXT (decl) == NULL_TREE)
    SET_DECL_ASSEMBLER_NAME (decl, DECL_NAME (decl));
  else
    {
      const char *name = IDENTIFIER_POINTER (DECL_NAME (decl));
      char *label;
      
      ASM_FORMAT_PRIVATE_NAME (label, name, DECL_UID (decl));
      SET_DECL_ASSEMBLER_NAME (decl, get_identifier (label));
    }
}