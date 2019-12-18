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
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 scalar_t__ INTEGRAL_OR_ENUMERATION_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ call_builtin_trap () ; 
 scalar_t__ convert_to_real (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ decay_conversion (scalar_t__) ; 
 int /*<<< orphan*/  double_type_node ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ perform_integral_promotions (scalar_t__) ; 
 int /*<<< orphan*/  pod_type_p (int /*<<< orphan*/ ) ; 
 scalar_t__ require_complete_type (scalar_t__) ; 
 int /*<<< orphan*/  skip_evaluation ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

tree
convert_arg_to_ellipsis (tree arg)
{
  /* [expr.call]

     The lvalue-to-rvalue, array-to-pointer, and function-to-pointer
     standard conversions are performed.  */
  arg = decay_conversion (arg);
  /* [expr.call]

     If the argument has integral or enumeration type that is subject
     to the integral promotions (_conv.prom_), or a floating point
     type that is subject to the floating point promotion
     (_conv.fpprom_), the value of the argument is converted to the
     promoted type before the call.  */
  if (TREE_CODE (TREE_TYPE (arg)) == REAL_TYPE
      && (TYPE_PRECISION (TREE_TYPE (arg))
	  < TYPE_PRECISION (double_type_node)))
    arg = convert_to_real (double_type_node, arg);
  else if (INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (arg)))
    arg = perform_integral_promotions (arg);

  arg = require_complete_type (arg);

  if (arg != error_mark_node
      && !pod_type_p (TREE_TYPE (arg)))
    {
      /* Undefined behavior [expr.call] 5.2.2/7.  We used to just warn
	 here and do a bitwise copy, but now cp_expr_size will abort if we
	 try to do that.
	 If the call appears in the context of a sizeof expression,
	 there is no need to emit a warning, since the expression won't be
	 evaluated. We keep the builtin_trap just as a safety check.  */
      if (!skip_evaluation)
	warning (0, "cannot pass objects of non-POD type %q#T through %<...%>; "
		 "call will abort at runtime", TREE_TYPE (arg));
      arg = call_builtin_trap ();
      arg = build2 (COMPOUND_EXPR, integer_type_node, arg,
		    integer_zero_node);
    }

  return arg;
}