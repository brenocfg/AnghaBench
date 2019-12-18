#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; scalar_t__ min; scalar_t__ max; int /*<<< orphan*/  equiv; } ;
typedef  TYPE_1__ value_range_t ;
typedef  scalar_t__ tree ;
struct loop {int /*<<< orphan*/  num; } ;
typedef  enum ev_direction { ____Placeholder_ev_direction } ev_direction ;
struct TYPE_6__ {int /*<<< orphan*/ * parray; } ;

/* Variables and functions */
 size_t CHREC_VARIABLE (scalar_t__) ; 
 int EV_DIR_DECREASES ; 
 int EV_DIR_UNKNOWN ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 scalar_t__ VR_ANTI_RANGE ; 
 scalar_t__ VR_RANGE ; 
 scalar_t__ VR_UNDEFINED ; 
 scalar_t__ VR_VARYING ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,scalar_t__) ; 
 int compare_values (scalar_t__,scalar_t__) ; 
 TYPE_3__* current_loops ; 
 scalar_t__ evolution_part_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ initial_condition_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ instantiate_parameters (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 scalar_t__ is_negative_overflow_infinity (scalar_t__) ; 
 scalar_t__ is_positive_overflow_infinity (scalar_t__) ; 
 scalar_t__ lower_bound_in_type (scalar_t__,scalar_t__) ; 
 int scev_direction (scalar_t__) ; 
 scalar_t__ scev_probably_wraps_p (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_value_range (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ upper_bound_in_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  valid_value_p (scalar_t__) ; 

__attribute__((used)) static void
adjust_range_with_scev (value_range_t *vr, struct loop *loop, tree stmt,
			tree var)
{
  tree init, step, chrec, tmin, tmax, min, max, type;
  enum ev_direction dir;

  /* TODO.  Don't adjust anti-ranges.  An anti-range may provide
     better opportunities than a regular range, but I'm not sure.  */
  if (vr->type == VR_ANTI_RANGE)
    return;

  chrec = instantiate_parameters (loop, analyze_scalar_evolution (loop, var));
  if (TREE_CODE (chrec) != POLYNOMIAL_CHREC)
    return;

  init = initial_condition_in_loop_num (chrec, loop->num);
  step = evolution_part_in_loop_num (chrec, loop->num);

  /* If STEP is symbolic, we can't know whether INIT will be the
     minimum or maximum value in the range.  Also, unless INIT is
     a simple expression, compare_values and possibly other functions
     in tree-vrp won't be able to handle it.  */
  if (step == NULL_TREE
      || !is_gimple_min_invariant (step)
      || !valid_value_p (init))
    return;

  dir = scev_direction (chrec);
  if (/* Do not adjust ranges if we do not know whether the iv increases
	 or decreases,  ... */
      dir == EV_DIR_UNKNOWN
      /* ... or if it may wrap.  */
      || scev_probably_wraps_p (init, step, stmt,
				current_loops->parray[CHREC_VARIABLE (chrec)],
				true))
    return;

  type = TREE_TYPE (var);

  /* If we see a pointer type starting at a constant, then we have an
     unusual ivopt.  It may legitimately wrap.  */
  if (POINTER_TYPE_P (type) && is_gimple_min_invariant (init))
    return;

  /* We use TYPE_MIN_VALUE and TYPE_MAX_VALUE here instead of
     negative_overflow_infinity and positive_overflow_infinity,
     because we have concluded that the loop probably does not
     wrap.  */

  if (POINTER_TYPE_P (type) || !TYPE_MIN_VALUE (type))
    tmin = lower_bound_in_type (type, type);
  else
    tmin = TYPE_MIN_VALUE (type);
  if (POINTER_TYPE_P (type) || !TYPE_MAX_VALUE (type))
    tmax = upper_bound_in_type (type, type);
  else
    tmax = TYPE_MAX_VALUE (type);

  if (vr->type == VR_VARYING || vr->type == VR_UNDEFINED)
    {
      min = tmin;
      max = tmax;

      /* For VARYING or UNDEFINED ranges, just about anything we get
	 from scalar evolutions should be better.  */

      if (dir == EV_DIR_DECREASES)
	max = init;
      else
	min = init;

      /* If we would create an invalid range, then just assume we
	 know absolutely nothing.  This may be over-conservative,
	 but it's clearly safe, and should happen only in unreachable
         parts of code, or for invalid programs.  */
      if (compare_values (min, max) == 1)
	return;

      set_value_range (vr, VR_RANGE, min, max, vr->equiv);
    }
  else if (vr->type == VR_RANGE)
    {
      min = vr->min;
      max = vr->max;

      if (dir == EV_DIR_DECREASES)
	{
	  /* INIT is the maximum value.  If INIT is lower than VR->MAX
	     but no smaller than VR->MIN, set VR->MAX to INIT.  */
	  if (compare_values (init, max) == -1)
	    {
	      max = init;

	      /* If we just created an invalid range with the minimum
		 greater than the maximum, we fail conservatively.
		 This should happen only in unreachable
		 parts of code, or for invalid programs.  */
	      if (compare_values (min, max) == 1)
		return;
	    }

	  /* According to the loop information, the variable does not
	     overflow.  If we think it does, probably because of an
	     overflow due to arithmetic on a different INF value,
	     reset now.  */
	  if (is_negative_overflow_infinity (min))
	    min = tmin;
	}
      else
	{
	  /* If INIT is bigger than VR->MIN, set VR->MIN to INIT.  */
	  if (compare_values (init, min) == 1)
	    {
	      min = init;

	      /* Again, avoid creating invalid range by failing.  */
	      if (compare_values (min, max) == 1)
		return;
	    }

	  if (is_positive_overflow_infinity (max))
	    max = tmax;
	}

      set_value_range (vr, VR_RANGE, min, max, vr->equiv);
    }
}