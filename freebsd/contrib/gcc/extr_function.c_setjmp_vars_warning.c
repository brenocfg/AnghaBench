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

/* Variables and functions */
 scalar_t__ BLOCK_SUBBLOCKS (scalar_t__) ; 
 scalar_t__ BLOCK_VARS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL (scalar_t__) ; 
 scalar_t__ DECL_RTL_SET_P (scalar_t__) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ regno_clobbered_at_setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
setjmp_vars_warning (tree block)
{
  tree decl, sub;

  for (decl = BLOCK_VARS (block); decl; decl = TREE_CHAIN (decl))
    {
      if (TREE_CODE (decl) == VAR_DECL
	  && DECL_RTL_SET_P (decl)
	  && REG_P (DECL_RTL (decl))
	  && regno_clobbered_at_setjmp (REGNO (DECL_RTL (decl))))
	warning (0, "variable %q+D might be clobbered by %<longjmp%>"
		 " or %<vfork%>",
		 decl);
    }

  for (sub = BLOCK_SUBBLOCKS (block); sub; sub = TREE_CHAIN (sub))
    setjmp_vars_warning (sub);
}