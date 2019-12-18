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
typedef  int /*<<< orphan*/  HARD_REG_SET ;
typedef  int /*<<< orphan*/  DECL_REGISTER ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_overlaps_hard_reg_set (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
tree_conflicts_with_clobbers_p (tree t, HARD_REG_SET *clobbered_regs)
{
  /* Conflicts between asm-declared register variables and the clobber
     list are not allowed.  */
  tree overlap = tree_overlaps_hard_reg_set (t, clobbered_regs);

  if (overlap)
    {
      error ("asm-specifier for variable %qs conflicts with asm clobber list",
	     IDENTIFIER_POINTER (DECL_NAME (overlap)));

      /* Reset registerness to stop multiple errors emitted for a single
	 variable.  */
      DECL_REGISTER (overlap) = 0;
      return true;
    }

  return false;
}