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
 int /*<<< orphan*/  PHI_ARG_DEF (int /*<<< orphan*/ ,int) ; 
 int PHI_NUM_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_uninit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
warn_uninitialized_phi (tree phi)
{
  int i, n = PHI_NUM_ARGS (phi);

  /* Don't look at memory tags.  */
  if (!is_gimple_reg (PHI_RESULT (phi)))
    return;

  for (i = 0; i < n; ++i)
    {
      tree op = PHI_ARG_DEF (phi, i);
      if (TREE_CODE (op) == SSA_NAME)
	warn_uninit (op, "%H%qD may be used uninitialized in this function",
		     NULL);
    }
}