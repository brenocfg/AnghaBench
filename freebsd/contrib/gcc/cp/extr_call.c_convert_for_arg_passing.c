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
struct TYPE_3__ {scalar_t__ (* promote_prototypes ) (scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 scalar_t__ COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ INT_CST_LT_UNSIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wmissing_format_attribute ; 
 int const POINTER_TYPE ; 
 int const REFERENCE_TYPE ; 
 scalar_t__ TREE_ADDRESSABLE (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_SIZE (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  build_reference_type (scalar_t__) ; 
 scalar_t__ check_missing_format_attribute (scalar_t__,scalar_t__) ; 
 scalar_t__ convert_to_integer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ is_bitfield_expr_with_lowered_type (scalar_t__) ; 
 scalar_t__ perform_integral_promotions (scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__) ; 
 TYPE_2__ targetm ; 
 scalar_t__ warn_missing_format_attribute ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
convert_for_arg_passing (tree type, tree val)
{
  tree bitfield_type;

  /* If VAL is a bitfield, then -- since it has already been converted
     to TYPE -- it cannot have a precision greater than TYPE.  

     If it has a smaller precision, we must widen it here.  For
     example, passing "int f:3;" to a function expecting an "int" will
     not result in any conversion before this point.

     If the precision is the same we must not risk widening.  For
     example, the COMPONENT_REF for a 32-bit "long long" bitfield will
     often have type "int", even though the C++ type for the field is
     "long long".  If the value is being passed to a function
     expecting an "int", then no conversions will be required.  But,
     if we call convert_bitfield_to_declared_type, the bitfield will
     be converted to "long long".  */
  bitfield_type = is_bitfield_expr_with_lowered_type (val);
  if (bitfield_type 
      && TYPE_PRECISION (TREE_TYPE (val)) < TYPE_PRECISION (type))
    val = convert_to_integer (TYPE_MAIN_VARIANT (bitfield_type), val);

  if (val == error_mark_node)
    ;
  /* Pass classes with copy ctors by invisible reference.  */
  else if (TREE_ADDRESSABLE (type))
    val = build1 (ADDR_EXPR, build_reference_type (type), val);
  else if (targetm.calls.promote_prototypes (type)
	   && INTEGRAL_TYPE_P (type)
	   && COMPLETE_TYPE_P (type)
	   && INT_CST_LT_UNSIGNED (TYPE_SIZE (type),
				   TYPE_SIZE (integer_type_node)))
    val = perform_integral_promotions (val);
  if (warn_missing_format_attribute)
    {
      tree rhstype = TREE_TYPE (val);
      const enum tree_code coder = TREE_CODE (rhstype);
      const enum tree_code codel = TREE_CODE (type);
      if ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	  && coder == codel
	  && check_missing_format_attribute (type, rhstype))
	warning (OPT_Wmissing_format_attribute,
		 "argument of function call might be a candidate for a format attribute");
    }
  return val;
}