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
 int /*<<< orphan*/  DECL_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_stack_protect ; 
 int optimize ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
defer_stack_allocation (tree var, bool toplevel)
{
  /* If stack protection is enabled, *all* stack variables must be deferred,
     so that we can re-order the strings to the top of the frame.  */
  if (flag_stack_protect)
    return true;

  /* Variables in the outermost scope automatically conflict with
     every other variable.  The only reason to want to defer them
     at all is that, after sorting, we can more efficiently pack
     small variables in the stack frame.  Continue to defer at -O2.  */
  if (toplevel && optimize < 2)
    return false;

  /* Without optimization, *most* variables are allocated from the
     stack, which makes the quadratic problem large exactly when we
     want compilation to proceed as quickly as possible.  On the
     other hand, we don't want the function's stack frame size to
     get completely out of hand.  So we avoid adding scalars and
     "small" aggregates to the list at all.  */
  if (optimize == 0 && tree_low_cst (DECL_SIZE_UNIT (var), 1) < 32)
    return false;

  return true;
}