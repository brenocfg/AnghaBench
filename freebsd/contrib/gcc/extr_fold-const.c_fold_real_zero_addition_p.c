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
 int /*<<< orphan*/  HONOR_SIGNED_ZEROS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HONOR_SIGN_DEPENDENT_ROUNDING (int /*<<< orphan*/ ) ; 
 scalar_t__ HONOR_SNANS (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ REAL_VALUE_MINUS_ZERO (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_zerop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
fold_real_zero_addition_p (tree type, tree addend, int negate)
{
  if (!real_zerop (addend))
    return false;

  /* Don't allow the fold with -fsignaling-nans.  */
  if (HONOR_SNANS (TYPE_MODE (type)))
    return false;

  /* Allow the fold if zeros aren't signed, or their sign isn't important.  */
  if (!HONOR_SIGNED_ZEROS (TYPE_MODE (type)))
    return true;

  /* Treat x + -0 as x - 0 and x - -0 as x + 0.  */
  if (TREE_CODE (addend) == REAL_CST
      && REAL_VALUE_MINUS_ZERO (TREE_REAL_CST (addend)))
    negate = !negate;

  /* The mode has signed zeros, and we have to honor their sign.
     In this situation, there is only one case we can return true for.
     X - 0 is the same as X unless rounding towards -infinity is
     supported.  */
  return negate && !HONOR_SIGN_DEPENDENT_ROUNDING (TYPE_MODE (type));
}