#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  equiv; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_RANGE ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_overflow_infinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_value (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_varying (TYPE_1__*) ; 
 int /*<<< orphan*/  vrp_evaluate_conditional_warnv (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void
extract_range_from_comparison (value_range_t *vr, tree expr)
{
  bool sop = false;
  tree val = vrp_evaluate_conditional_warnv (expr, false, &sop);

  /* A disadvantage of using a special infinity as an overflow
     representation is that we lose the ability to record overflow
     when we don't have an infinity.  So we have to ignore a result
     which relies on overflow.  */

  if (val && !is_overflow_infinity (val) && !sop)
    {
      /* Since this expression was found on the RHS of an assignment,
	 its type may be different from _Bool.  Convert VAL to EXPR's
	 type.  */
      val = fold_convert (TREE_TYPE (expr), val);
      if (is_gimple_min_invariant (val))
	set_value_range_to_value (vr, val, vr->equiv);
      else
	set_value_range (vr, VR_RANGE, val, val, vr->equiv);
    }
  else
    set_value_range_to_varying (vr);
}