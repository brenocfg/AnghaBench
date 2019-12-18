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
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ASSEMBLER_NAME_SET_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_COMDAT (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_SYMBOL_REFERENCED (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_USED (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int at_eof ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

bool
decl_needed_p (tree decl)
{
  gcc_assert (TREE_CODE (decl) == VAR_DECL
	      || TREE_CODE (decl) == FUNCTION_DECL);
  /* This function should only be called at the end of the translation
     unit.  We cannot be sure of whether or not something will be
     COMDAT until that point.  */
  gcc_assert (at_eof);

  /* All entities with external linkage that are not COMDAT should be
     emitted; they may be referred to from other object files.  */
  if (TREE_PUBLIC (decl) && !DECL_COMDAT (decl))
    return true;
  /* If this entity was used, let the back-end see it; it will decide
     whether or not to emit it into the object file.  */
  if (TREE_USED (decl)
      || (DECL_ASSEMBLER_NAME_SET_P (decl)
	  && TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl))))
      return true;
  /* Otherwise, DECL does not need to be emitted -- yet.  A subsequent
     reference to DECL might cause it to be emitted later.  */
  return false;
}