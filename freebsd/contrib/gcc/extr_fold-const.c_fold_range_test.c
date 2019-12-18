#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_3__ {scalar_t__ (* global_bindings_p ) () ;} ;
struct TYPE_4__ {TYPE_1__ decls; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTAINS_PLACEHOLDER_P (scalar_t__) ; 
 char* G_ (char*) ; 
 scalar_t__ LOGICAL_OP_NON_SHORT_CIRCUIT ; 
 int TRUTH_ANDIF_EXPR ; 
 int TRUTH_AND_EXPR ; 
 int TRUTH_ORIF_EXPR ; 
 int TRUTH_OR_EXPR ; 
 int /*<<< orphan*/  WARN_STRICT_OVERFLOW_COMPARISON ; 
 scalar_t__ build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_range_check (scalar_t__,scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fold_overflow_warning (char const* const,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zero_node ; 
 scalar_t__ invert_truthvalue (scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 scalar_t__ make_range (scalar_t__,int*,scalar_t__*,scalar_t__*,int*) ; 
 scalar_t__ merge_ranges (int*,scalar_t__*,scalar_t__*,int,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__) ; 
 scalar_t__ operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ save_expr (scalar_t__) ; 
 scalar_t__ simple_operand_p (scalar_t__) ; 
 scalar_t__ stub1 () ; 

__attribute__((used)) static tree
fold_range_test (enum tree_code code, tree type, tree op0, tree op1)
{
  int or_op = (code == TRUTH_ORIF_EXPR
	       || code == TRUTH_OR_EXPR);
  int in0_p, in1_p, in_p;
  tree low0, low1, low, high0, high1, high;
  bool strict_overflow_p = false;
  tree lhs = make_range (op0, &in0_p, &low0, &high0, &strict_overflow_p);
  tree rhs = make_range (op1, &in1_p, &low1, &high1, &strict_overflow_p);
  tree tem;
  const char * const warnmsg = G_("assuming signed overflow does not occur "
				  "when simplifying range test");

  /* If this is an OR operation, invert both sides; we will invert
     again at the end.  */
  if (or_op)
    in0_p = ! in0_p, in1_p = ! in1_p;

  /* If both expressions are the same, if we can merge the ranges, and we
     can build the range test, return it or it inverted.  If one of the
     ranges is always true or always false, consider it to be the same
     expression as the other.  */
  if ((lhs == 0 || rhs == 0 || operand_equal_p (lhs, rhs, 0))
      && merge_ranges (&in_p, &low, &high, in0_p, low0, high0,
		       in1_p, low1, high1)
      && 0 != (tem = (build_range_check (type,
					 lhs != 0 ? lhs
					 : rhs != 0 ? rhs : integer_zero_node,
					 in_p, low, high))))
    {
      if (strict_overflow_p)
	fold_overflow_warning (warnmsg, WARN_STRICT_OVERFLOW_COMPARISON);
      return or_op ? invert_truthvalue (tem) : tem;
    }

  /* On machines where the branch cost is expensive, if this is a
     short-circuited branch and the underlying object on both sides
     is the same, make a non-short-circuit operation.  */
  else if (LOGICAL_OP_NON_SHORT_CIRCUIT
	   && lhs != 0 && rhs != 0
	   && (code == TRUTH_ANDIF_EXPR
	       || code == TRUTH_ORIF_EXPR)
	   && operand_equal_p (lhs, rhs, 0))
    {
      /* If simple enough, just rewrite.  Otherwise, make a SAVE_EXPR
	 unless we are at top level or LHS contains a PLACEHOLDER_EXPR, in
	 which cases we can't do this.  */
      if (simple_operand_p (lhs))
	return build2 (code == TRUTH_ANDIF_EXPR
		       ? TRUTH_AND_EXPR : TRUTH_OR_EXPR,
		       type, op0, op1);

      else if (lang_hooks.decls.global_bindings_p () == 0
	       && ! CONTAINS_PLACEHOLDER_P (lhs))
	{
	  tree common = save_expr (lhs);

	  if (0 != (lhs = build_range_check (type, common,
					     or_op ? ! in0_p : in0_p,
					     low0, high0))
	      && (0 != (rhs = build_range_check (type, common,
						 or_op ? ! in1_p : in1_p,
						 low1, high1))))
	    {
	      if (strict_overflow_p)
		fold_overflow_warning (warnmsg,
				       WARN_STRICT_OVERFLOW_COMPARISON);
	      return build2 (code == TRUTH_ANDIF_EXPR
			     ? TRUTH_AND_EXPR : TRUTH_OR_EXPR,
			     type, lhs, rhs);
	    }
	}
    }

  return 0;
}