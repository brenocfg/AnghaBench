#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ member_0; scalar_t__ member_1; scalar_t__ member_2; scalar_t__ type; scalar_t__ min; scalar_t__ max; int /*<<< orphan*/ * member_3; } ;
typedef  TYPE_1__ value_range_t ;
typedef  scalar_t__ tree ;
typedef  enum value_range_type { ____Placeholder_value_range_type } value_range_type ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int BIT_AND_EXPR ; 
 int CEIL_DIV_EXPR ; 
 int EXACT_DIV_EXPR ; 
 int FLOOR_DIV_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int MAX_EXPR ; 
 int MINUS_EXPR ; 
 int MIN_EXPR ; 
 int MULT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int PLUS_EXPR ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int ROUND_DIV_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int TRUNC_DIV_EXPR ; 
 int TRUTH_ANDIF_EXPR ; 
 int TRUTH_AND_EXPR ; 
 int TRUTH_ORIF_EXPR ; 
 int TRUTH_OR_EXPR ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_UNDEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ VR_ANTI_RANGE ; 
 scalar_t__ VR_RANGE ; 
 scalar_t__ VR_UNDEFINED ; 
 scalar_t__ VR_VARYING ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int) ; 
 int compare_values (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_binary (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_1__* get_value_range (scalar_t__) ; 
 scalar_t__ integer_onep (scalar_t__) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 scalar_t__ is_overflow_infinity (scalar_t__) ; 
 int /*<<< orphan*/  overflow_infinity_range_p (TYPE_1__*) ; 
 scalar_t__ range_includes_zero_p (TYPE_1__*) ; 
 scalar_t__ range_is_nonnull (TYPE_1__*) ; 
 scalar_t__ range_is_null (TYPE_1__*) ; 
 int /*<<< orphan*/  set_value_range (TYPE_1__*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_value_range_to_nonnull (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_null (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range_to_undefined (TYPE_1__*) ; 
 int /*<<< orphan*/  set_value_range_to_value (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_value_range_to_varying (TYPE_1__*) ; 
 scalar_t__ symbolic_range_p (TYPE_1__*) ; 
 scalar_t__ tree_int_cst_sgn (scalar_t__) ; 
 scalar_t__ vrp_int_const_binop (int,scalar_t__,scalar_t__) ; 
 scalar_t__ vrp_val_is_max (scalar_t__) ; 
 scalar_t__ vrp_val_is_min (scalar_t__) ; 

__attribute__((used)) static void
extract_range_from_binary_expr (value_range_t *vr, tree expr)
{
  enum tree_code code = TREE_CODE (expr);
  enum value_range_type type;
  tree op0, op1, min, max;
  int cmp;
  value_range_t vr0 = { VR_UNDEFINED, NULL_TREE, NULL_TREE, NULL };
  value_range_t vr1 = { VR_UNDEFINED, NULL_TREE, NULL_TREE, NULL };

  /* Not all binary expressions can be applied to ranges in a
     meaningful way.  Handle only arithmetic operations.  */
  if (code != PLUS_EXPR
      && code != MINUS_EXPR
      && code != MULT_EXPR
      && code != TRUNC_DIV_EXPR
      && code != FLOOR_DIV_EXPR
      && code != CEIL_DIV_EXPR
      && code != EXACT_DIV_EXPR
      && code != ROUND_DIV_EXPR
      && code != MIN_EXPR
      && code != MAX_EXPR
      && code != BIT_AND_EXPR
      && code != TRUTH_ANDIF_EXPR
      && code != TRUTH_ORIF_EXPR
      && code != TRUTH_AND_EXPR
      && code != TRUTH_OR_EXPR)
    {
      set_value_range_to_varying (vr);
      return;
    }

  /* Get value ranges for each operand.  For constant operands, create
     a new value range with the operand to simplify processing.  */
  op0 = TREE_OPERAND (expr, 0);
  if (TREE_CODE (op0) == SSA_NAME)
    vr0 = *(get_value_range (op0));
  else if (is_gimple_min_invariant (op0))
    set_value_range_to_value (&vr0, op0, NULL);
  else
    set_value_range_to_varying (&vr0);

  op1 = TREE_OPERAND (expr, 1);
  if (TREE_CODE (op1) == SSA_NAME)
    vr1 = *(get_value_range (op1));
  else if (is_gimple_min_invariant (op1))
    set_value_range_to_value (&vr1, op1, NULL);
  else
    set_value_range_to_varying (&vr1);

  /* If either range is UNDEFINED, so is the result.  */
  if (vr0.type == VR_UNDEFINED || vr1.type == VR_UNDEFINED)
    {
      set_value_range_to_undefined (vr);
      return;
    }

  /* The type of the resulting value range defaults to VR0.TYPE.  */
  type = vr0.type;

  /* Refuse to operate on VARYING ranges, ranges of different kinds
     and symbolic ranges.  As an exception, we allow BIT_AND_EXPR
     because we may be able to derive a useful range even if one of
     the operands is VR_VARYING or symbolic range.  TODO, we may be
     able to derive anti-ranges in some cases.  */
  if (code != BIT_AND_EXPR
      && code != TRUTH_AND_EXPR
      && code != TRUTH_OR_EXPR
      && (vr0.type == VR_VARYING
	  || vr1.type == VR_VARYING
	  || vr0.type != vr1.type
	  || symbolic_range_p (&vr0)
	  || symbolic_range_p (&vr1)))
    {
      set_value_range_to_varying (vr);
      return;
    }

  /* Now evaluate the expression to determine the new range.  */
  if (POINTER_TYPE_P (TREE_TYPE (expr))
      || POINTER_TYPE_P (TREE_TYPE (op0))
      || POINTER_TYPE_P (TREE_TYPE (op1)))
    {
      /* For pointer types, we are really only interested in asserting
	 whether the expression evaluates to non-NULL.  FIXME, we used
	 to gcc_assert (code == PLUS_EXPR || code == MINUS_EXPR), but
	 ivopts is generating expressions with pointer multiplication
	 in them.  */
      if (code == PLUS_EXPR)
	{
	  if (range_is_nonnull (&vr0) || range_is_nonnull (&vr1))
	    set_value_range_to_nonnull (vr, TREE_TYPE (expr));
	  else if (range_is_null (&vr0) && range_is_null (&vr1))
	    set_value_range_to_null (vr, TREE_TYPE (expr));
	  else
	    set_value_range_to_varying (vr);
	}
      else
	{
	  /* Subtracting from a pointer, may yield 0, so just drop the
	     resulting range to varying.  */
	  set_value_range_to_varying (vr);
	}

      return;
    }

  /* For integer ranges, apply the operation to each end of the
     range and see what we end up with.  */
  if (code == TRUTH_ANDIF_EXPR
      || code == TRUTH_ORIF_EXPR
      || code == TRUTH_AND_EXPR
      || code == TRUTH_OR_EXPR)
    {
      /* If one of the operands is zero, we know that the whole
	 expression evaluates zero.  */
      if (code == TRUTH_AND_EXPR
	  && ((vr0.type == VR_RANGE
	       && integer_zerop (vr0.min)
	       && integer_zerop (vr0.max))
	      || (vr1.type == VR_RANGE
		  && integer_zerop (vr1.min)
		  && integer_zerop (vr1.max))))
	{
	  type = VR_RANGE;
	  min = max = build_int_cst (TREE_TYPE (expr), 0);
	}
      /* If one of the operands is one, we know that the whole
	 expression evaluates one.  */
      else if (code == TRUTH_OR_EXPR
	       && ((vr0.type == VR_RANGE
		    && integer_onep (vr0.min)
		    && integer_onep (vr0.max))
		   || (vr1.type == VR_RANGE
		       && integer_onep (vr1.min)
		       && integer_onep (vr1.max))))
	{
	  type = VR_RANGE;
	  min = max = build_int_cst (TREE_TYPE (expr), 1);
	}
      else if (vr0.type != VR_VARYING
	       && vr1.type != VR_VARYING
	       && vr0.type == vr1.type
	       && !symbolic_range_p (&vr0)
	       && !overflow_infinity_range_p (&vr0)
	       && !symbolic_range_p (&vr1)
	       && !overflow_infinity_range_p (&vr1))
	{
	  /* Boolean expressions cannot be folded with int_const_binop.  */
	  min = fold_binary (code, TREE_TYPE (expr), vr0.min, vr1.min);
	  max = fold_binary (code, TREE_TYPE (expr), vr0.max, vr1.max);
	}
      else
	{
	  set_value_range_to_varying (vr);
	  return;
	}
    }
  else if (code == PLUS_EXPR
	   || code == MIN_EXPR
	   || code == MAX_EXPR)
    {
      /* If we have a PLUS_EXPR with two VR_ANTI_RANGEs, drop to
	 VR_VARYING.  It would take more effort to compute a precise
	 range for such a case.  For example, if we have op0 == 1 and
	 op1 == -1 with their ranges both being ~[0,0], we would have
	 op0 + op1 == 0, so we cannot claim that the sum is in ~[0,0].
	 Note that we are guaranteed to have vr0.type == vr1.type at
	 this point.  */
      if (code == PLUS_EXPR && vr0.type == VR_ANTI_RANGE)
	{
	  set_value_range_to_varying (vr);
	  return;
	}

      /* For operations that make the resulting range directly
	 proportional to the original ranges, apply the operation to
	 the same end of each range.  */
      min = vrp_int_const_binop (code, vr0.min, vr1.min);
      max = vrp_int_const_binop (code, vr0.max, vr1.max);
    }
  else if (code == MULT_EXPR
	   || code == TRUNC_DIV_EXPR
	   || code == FLOOR_DIV_EXPR
	   || code == CEIL_DIV_EXPR
	   || code == EXACT_DIV_EXPR
	   || code == ROUND_DIV_EXPR)
    {
      tree val[4];
      size_t i;
      bool sop;

      /* If we have an unsigned MULT_EXPR with two VR_ANTI_RANGEs,
	 drop to VR_VARYING.  It would take more effort to compute a
	 precise range for such a case.  For example, if we have
	 op0 == 65536 and op1 == 65536 with their ranges both being
	 ~[0,0] on a 32-bit machine, we would have op0 * op1 == 0, so
	 we cannot claim that the product is in ~[0,0].  Note that we
	 are guaranteed to have vr0.type == vr1.type at this
	 point.  */
      if (code == MULT_EXPR
	  && vr0.type == VR_ANTI_RANGE
	  && !TYPE_OVERFLOW_UNDEFINED (TREE_TYPE (op0)))
	{
	  set_value_range_to_varying (vr);
	  return;
	}

      /* Multiplications and divisions are a bit tricky to handle,
	 depending on the mix of signs we have in the two ranges, we
	 need to operate on different values to get the minimum and
	 maximum values for the new range.  One approach is to figure
	 out all the variations of range combinations and do the
	 operations.

	 However, this involves several calls to compare_values and it
	 is pretty convoluted.  It's simpler to do the 4 operations
	 (MIN0 OP MIN1, MIN0 OP MAX1, MAX0 OP MIN1 and MAX0 OP MAX0 OP
	 MAX1) and then figure the smallest and largest values to form
	 the new range.  */

      /* Divisions by zero result in a VARYING value.  */
      if (code != MULT_EXPR
	  && (vr0.type == VR_ANTI_RANGE || range_includes_zero_p (&vr1)))
	{
	  set_value_range_to_varying (vr);
	  return;
	}

      /* Compute the 4 cross operations.  */
      sop = false;
      val[0] = vrp_int_const_binop (code, vr0.min, vr1.min);
      if (val[0] == NULL_TREE)
	sop = true;

      if (vr1.max == vr1.min)
	val[1] = NULL_TREE;
      else
	{
	  val[1] = vrp_int_const_binop (code, vr0.min, vr1.max);
	  if (val[1] == NULL_TREE)
	    sop = true;
	}

      if (vr0.max == vr0.min)
	val[2] = NULL_TREE;
      else
	{
	  val[2] = vrp_int_const_binop (code, vr0.max, vr1.min);
	  if (val[2] == NULL_TREE)
	    sop = true;
	}

      if (vr0.min == vr0.max || vr1.min == vr1.max)
	val[3] = NULL_TREE;
      else
	{
	  val[3] = vrp_int_const_binop (code, vr0.max, vr1.max);
	  if (val[3] == NULL_TREE)
	    sop = true;
	}

      if (sop)
	{
	  set_value_range_to_varying (vr);
	  return;
	}

      /* Set MIN to the minimum of VAL[i] and MAX to the maximum
	 of VAL[i].  */
      min = val[0];
      max = val[0];
      for (i = 1; i < 4; i++)
	{
	  if (!is_gimple_min_invariant (min)
	      || (TREE_OVERFLOW (min) && !is_overflow_infinity (min))
	      || !is_gimple_min_invariant (max)
	      || (TREE_OVERFLOW (max) && !is_overflow_infinity (max)))
	    break;

	  if (val[i])
	    {
	      if (!is_gimple_min_invariant (val[i])
		  || (TREE_OVERFLOW (val[i])
		      && !is_overflow_infinity (val[i])))
		{
		  /* If we found an overflowed value, set MIN and MAX
		     to it so that we set the resulting range to
		     VARYING.  */
		  min = max = val[i];
		  break;
		}

	      if (compare_values (val[i], min) == -1)
		min = val[i];

	      if (compare_values (val[i], max) == 1)
		max = val[i];
	    }
	}
    }
  else if (code == MINUS_EXPR)
    {
      /* If we have a MINUS_EXPR with two VR_ANTI_RANGEs, drop to
	 VR_VARYING.  It would take more effort to compute a precise
	 range for such a case.  For example, if we have op0 == 1 and
	 op1 == 1 with their ranges both being ~[0,0], we would have
	 op0 - op1 == 0, so we cannot claim that the difference is in
	 ~[0,0].  Note that we are guaranteed to have
	 vr0.type == vr1.type at this point.  */
      if (vr0.type == VR_ANTI_RANGE)
	{
	  set_value_range_to_varying (vr);
	  return;
	}

      /* For MINUS_EXPR, apply the operation to the opposite ends of
	 each range.  */
      min = vrp_int_const_binop (code, vr0.min, vr1.max);
      max = vrp_int_const_binop (code, vr0.max, vr1.min);
    }
  else if (code == BIT_AND_EXPR)
    {
      if (vr0.type == VR_RANGE
	  && vr0.min == vr0.max
	  && TREE_CODE (vr0.max) == INTEGER_CST
	  && !TREE_OVERFLOW (vr0.max)
	  && tree_int_cst_sgn (vr0.max) >= 0)
	{
	  min = build_int_cst (TREE_TYPE (expr), 0);
	  max = vr0.max;
	}
      else if (vr1.type == VR_RANGE
	       && vr1.min == vr1.max
	       && TREE_CODE (vr1.max) == INTEGER_CST
	       && !TREE_OVERFLOW (vr1.max)
	       && tree_int_cst_sgn (vr1.max) >= 0)
	{
	  type = VR_RANGE;
	  min = build_int_cst (TREE_TYPE (expr), 0);
	  max = vr1.max;
	}
      else
	{
	  set_value_range_to_varying (vr);
	  return;
	}
    }
  else
    gcc_unreachable ();

  /* If either MIN or MAX overflowed, then set the resulting range to
     VARYING.  But we do accept an overflow infinity
     representation.  */
  if (min == NULL_TREE
      || !is_gimple_min_invariant (min)
      || (TREE_OVERFLOW (min) && !is_overflow_infinity (min))
      || max == NULL_TREE
      || !is_gimple_min_invariant (max)
      || (TREE_OVERFLOW (max) && !is_overflow_infinity (max)))
    {
      set_value_range_to_varying (vr);
      return;
    }

  /* We punt if:
     1) [-INF, +INF]
     2) [-INF, +-INF(OVF)]
     3) [+-INF(OVF), +INF]
     4) [+-INF(OVF), +-INF(OVF)]
     We learn nothing when we have INF and INF(OVF) on both sides.
     Note that we do accept [-INF, -INF] and [+INF, +INF] without
     overflow.  */
  if ((vrp_val_is_min (min) || is_overflow_infinity (min))
      && (vrp_val_is_max (max) || is_overflow_infinity (max)))
    {
      set_value_range_to_varying (vr);
      return;
    }

  cmp = compare_values (min, max);
  if (cmp == -2 || cmp == 1)
    {
      /* If the new range has its limits swapped around (MIN > MAX),
	 then the operation caused one of them to wrap around, mark
	 the new range VARYING.  */
      set_value_range_to_varying (vr);
    }
  else
    set_value_range (vr, type, min, max, NULL);
}