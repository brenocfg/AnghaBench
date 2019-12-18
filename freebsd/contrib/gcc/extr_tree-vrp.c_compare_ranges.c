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
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int EQ_EXPR ; 
 int GE_EXPR ; 
 int GT_EXPR ; 
 int LE_EXPR ; 
 int LT_EXPR ; 
 int NE_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ VR_ANTI_RANGE ; 
 scalar_t__ VR_RANGE ; 
 scalar_t__ VR_UNDEFINED ; 
 scalar_t__ VR_VARYING ; 
 int /*<<< orphan*/  boolean_false_node ; 
 int /*<<< orphan*/  boolean_true_node ; 
 int compare_values_warnv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ overflow_infinity_range_p (TYPE_1__*) ; 
 int /*<<< orphan*/  usable_range_p (TYPE_1__*,int*) ; 

__attribute__((used)) static tree
compare_ranges (enum tree_code comp, value_range_t *vr0, value_range_t *vr1,
		bool *strict_overflow_p)
{
  /* VARYING or UNDEFINED ranges cannot be compared.  */
  if (vr0->type == VR_VARYING
      || vr0->type == VR_UNDEFINED
      || vr1->type == VR_VARYING
      || vr1->type == VR_UNDEFINED)
    return NULL_TREE;

  /* Anti-ranges need to be handled separately.  */
  if (vr0->type == VR_ANTI_RANGE || vr1->type == VR_ANTI_RANGE)
    {
      /* If both are anti-ranges, then we cannot compute any
	 comparison.  */
      if (vr0->type == VR_ANTI_RANGE && vr1->type == VR_ANTI_RANGE)
	return NULL_TREE;

      /* These comparisons are never statically computable.  */
      if (comp == GT_EXPR
	  || comp == GE_EXPR
	  || comp == LT_EXPR
	  || comp == LE_EXPR)
	return NULL_TREE;

      /* Equality can be computed only between a range and an
	 anti-range.  ~[VAL1, VAL2] == [VAL1, VAL2] is always false.  */
      if (vr0->type == VR_RANGE)
	{
	  /* To simplify processing, make VR0 the anti-range.  */
	  value_range_t *tmp = vr0;
	  vr0 = vr1;
	  vr1 = tmp;
	}

      gcc_assert (comp == NE_EXPR || comp == EQ_EXPR);

      if (compare_values_warnv (vr0->min, vr1->min, strict_overflow_p) == 0
	  && compare_values_warnv (vr0->max, vr1->max, strict_overflow_p) == 0)
	return (comp == NE_EXPR) ? boolean_true_node : boolean_false_node;

      return NULL_TREE;
    }

  if (!usable_range_p (vr0, strict_overflow_p)
      || !usable_range_p (vr1, strict_overflow_p))
    return NULL_TREE;

  /* Simplify processing.  If COMP is GT_EXPR or GE_EXPR, switch the
     operands around and change the comparison code.  */
  if (comp == GT_EXPR || comp == GE_EXPR)
    {
      value_range_t *tmp;
      comp = (comp == GT_EXPR) ? LT_EXPR : LE_EXPR;
      tmp = vr0;
      vr0 = vr1;
      vr1 = tmp;
    }

  if (comp == EQ_EXPR)
    {
      /* Equality may only be computed if both ranges represent
	 exactly one value.  */
      if (compare_values_warnv (vr0->min, vr0->max, strict_overflow_p) == 0
	  && compare_values_warnv (vr1->min, vr1->max, strict_overflow_p) == 0)
	{
	  int cmp_min = compare_values_warnv (vr0->min, vr1->min,
					      strict_overflow_p);
	  int cmp_max = compare_values_warnv (vr0->max, vr1->max,
					      strict_overflow_p);
	  if (cmp_min == 0 && cmp_max == 0)
	    return boolean_true_node;
	  else if (cmp_min != -2 && cmp_max != -2)
	    return boolean_false_node;
	}
      /* If [V0_MIN, V1_MAX] < [V1_MIN, V1_MAX] then V0 != V1.  */
      else if (compare_values_warnv (vr0->min, vr1->max,
				     strict_overflow_p) == 1
	       || compare_values_warnv (vr1->min, vr0->max,
					strict_overflow_p) == 1)
	return boolean_false_node;

      return NULL_TREE;
    }
  else if (comp == NE_EXPR)
    {
      int cmp1, cmp2;

      /* If VR0 is completely to the left or completely to the right
	 of VR1, they are always different.  Notice that we need to
	 make sure that both comparisons yield similar results to
	 avoid comparing values that cannot be compared at
	 compile-time.  */
      cmp1 = compare_values_warnv (vr0->max, vr1->min, strict_overflow_p);
      cmp2 = compare_values_warnv (vr0->min, vr1->max, strict_overflow_p);
      if ((cmp1 == -1 && cmp2 == -1) || (cmp1 == 1 && cmp2 == 1))
	return boolean_true_node;

      /* If VR0 and VR1 represent a single value and are identical,
	 return false.  */
      else if (compare_values_warnv (vr0->min, vr0->max,
				     strict_overflow_p) == 0
	       && compare_values_warnv (vr1->min, vr1->max,
					strict_overflow_p) == 0
	       && compare_values_warnv (vr0->min, vr1->min,
					strict_overflow_p) == 0
	       && compare_values_warnv (vr0->max, vr1->max,
					strict_overflow_p) == 0)
	return boolean_false_node;

      /* Otherwise, they may or may not be different.  */
      else
	return NULL_TREE;
    }
  else if (comp == LT_EXPR || comp == LE_EXPR)
    {
      int tst;

      /* If VR0 is to the left of VR1, return true.  */
      tst = compare_values_warnv (vr0->max, vr1->min, strict_overflow_p);
      if ((comp == LT_EXPR && tst == -1)
	  || (comp == LE_EXPR && (tst == -1 || tst == 0)))
	{
	  if (overflow_infinity_range_p (vr0)
	      || overflow_infinity_range_p (vr1))
	    *strict_overflow_p = true;
	  return boolean_true_node;
	}

      /* If VR0 is to the right of VR1, return false.  */
      tst = compare_values_warnv (vr0->min, vr1->max, strict_overflow_p);
      if ((comp == LT_EXPR && (tst == 0 || tst == 1))
	  || (comp == LE_EXPR && tst == 1))
	{
	  if (overflow_infinity_range_p (vr0)
	      || overflow_infinity_range_p (vr1))
	    *strict_overflow_p = true;
	  return boolean_false_node;
	}

      /* Otherwise, we don't know.  */
      return NULL_TREE;
    }
    
  gcc_unreachable ();
}