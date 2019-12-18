#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ type; scalar_t__ equiv; int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VR_ANTI_RANGE ; 
 scalar_t__ VR_RANGE ; 
 scalar_t__ VR_UNDEFINED ; 
 scalar_t__ VR_VARYING ; 
 int /*<<< orphan*/  bitmap_and_into (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_clear (scalar_t__) ; 
 int compare_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_value_range (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ is_overflow_infinity (int /*<<< orphan*/ ) ; 
 scalar_t__ range_includes_zero_p (TYPE_1__*) ; 
 int /*<<< orphan*/  set_value_range (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_value_range_to_nonnull (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_varying (TYPE_1__*) ; 
 int /*<<< orphan*/  symbolic_range_p (TYPE_1__*) ; 
 scalar_t__ value_ranges_intersect_p (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ vrp_val_is_max (int /*<<< orphan*/ ) ; 
 scalar_t__ vrp_val_is_min (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vrp_meet (value_range_t *vr0, value_range_t *vr1)
{
  if (vr0->type == VR_UNDEFINED)
    {
      copy_value_range (vr0, vr1);
      return;
    }

  if (vr1->type == VR_UNDEFINED)
    {
      /* Nothing to do.  VR0 already has the resulting range.  */
      return;
    }

  if (vr0->type == VR_VARYING)
    {
      /* Nothing to do.  VR0 already has the resulting range.  */
      return;
    }

  if (vr1->type == VR_VARYING)
    {
      set_value_range_to_varying (vr0);
      return;
    }

  if (vr0->type == VR_RANGE && vr1->type == VR_RANGE)
    {
      /* If VR0 and VR1 have a non-empty intersection, compute the
	 union of both ranges.  */
      if (value_ranges_intersect_p (vr0, vr1))
	{
	  int cmp;
	  tree min, max;

	  /* The lower limit of the new range is the minimum of the
	     two ranges.  If they cannot be compared, the result is
	     VARYING.  */
	  cmp = compare_values (vr0->min, vr1->min);
	  if (cmp == 0 || cmp == 1)
	    min = vr1->min;
	  else if (cmp == -1)
	    min = vr0->min;
	  else
	    {
	      set_value_range_to_varying (vr0);
	      return;
	    }

	  /* Similarly, the upper limit of the new range is the
	     maximum of the two ranges.  If they cannot be compared,
	     the result is VARYING.  */
	  cmp = compare_values (vr0->max, vr1->max);
	  if (cmp == 0 || cmp == -1)
	    max = vr1->max;
	  else if (cmp == 1)
	    max = vr0->max;
	  else
	    {
	      set_value_range_to_varying (vr0);
	      return;
	    }

	  /* Check for useless ranges.  */
	  if (INTEGRAL_TYPE_P (TREE_TYPE (min))
	      && ((vrp_val_is_min (min) || is_overflow_infinity (min))
		  && (vrp_val_is_max (max) || is_overflow_infinity (max))))
	    {
	      set_value_range_to_varying (vr0);
	      return;
	    }

	  /* The resulting set of equivalences is the intersection of
	     the two sets.  */
	  if (vr0->equiv && vr1->equiv && vr0->equiv != vr1->equiv)
	    bitmap_and_into (vr0->equiv, vr1->equiv);
	  else if (vr0->equiv && !vr1->equiv)
	    bitmap_clear (vr0->equiv);

	  set_value_range (vr0, vr0->type, min, max, vr0->equiv);
	}
      else
	goto no_meet;
    }
  else if (vr0->type == VR_ANTI_RANGE && vr1->type == VR_ANTI_RANGE)
    {
      /* Two anti-ranges meet only if they are both identical.  */
      if (compare_values (vr0->min, vr1->min) == 0
	  && compare_values (vr0->max, vr1->max) == 0
	  && compare_values (vr0->min, vr0->max) == 0)
	{
	  /* The resulting set of equivalences is the intersection of
	     the two sets.  */
	  if (vr0->equiv && vr1->equiv && vr0->equiv != vr1->equiv)
	    bitmap_and_into (vr0->equiv, vr1->equiv);
	  else if (vr0->equiv && !vr1->equiv)
	    bitmap_clear (vr0->equiv);
	}
      else
	goto no_meet;
    }
  else if (vr0->type == VR_ANTI_RANGE || vr1->type == VR_ANTI_RANGE)
    {
      /* A numeric range [VAL1, VAL2] and an anti-range ~[VAL3, VAL4]
	 meet only if the ranges have an empty intersection.  The
	 result of the meet operation is the anti-range.  */
      if (!symbolic_range_p (vr0)
	  && !symbolic_range_p (vr1)
	  && !value_ranges_intersect_p (vr0, vr1))
	{
	  /* Copy most of VR1 into VR0.  Don't copy VR1's equivalence
	     set.  We need to compute the intersection of the two
	     equivalence sets.  */
	  if (vr1->type == VR_ANTI_RANGE)
	    set_value_range (vr0, vr1->type, vr1->min, vr1->max, vr0->equiv);

	  /* The resulting set of equivalences is the intersection of
	     the two sets.  */
	  if (vr0->equiv && vr1->equiv && vr0->equiv != vr1->equiv)
	    bitmap_and_into (vr0->equiv, vr1->equiv);
	  else if (vr0->equiv && !vr1->equiv)
	    bitmap_clear (vr0->equiv);
	}
      else
	goto no_meet;
    }
  else
    gcc_unreachable ();

  return;

no_meet:
  /* The two range VR0 and VR1 do not meet.  Before giving up and
     setting the result to VARYING, see if we can at least derive a
     useful anti-range.  FIXME, all this nonsense about distinguishing
     anti-ranges from ranges is necessary because of the odd
     semantics of range_includes_zero_p and friends.  */
  if (!symbolic_range_p (vr0)
      && ((vr0->type == VR_RANGE && !range_includes_zero_p (vr0))
	  || (vr0->type == VR_ANTI_RANGE && range_includes_zero_p (vr0)))
      && !symbolic_range_p (vr1)
      && ((vr1->type == VR_RANGE && !range_includes_zero_p (vr1))
	  || (vr1->type == VR_ANTI_RANGE && range_includes_zero_p (vr1))))
    {
      set_value_range_to_nonnull (vr0, TREE_TYPE (vr0->min));

      /* Since this meet operation did not result from the meeting of
	 two equivalent names, VR0 cannot have any equivalences.  */
      if (vr0->equiv)
	bitmap_clear (vr0->equiv);
    }
  else
    set_value_range_to_varying (vr0);
}