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
 scalar_t__ ENUMERAL_TYPE ; 
 int /*<<< orphan*/  INTEGRAL_OR_ENUMERATION_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ cp_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ is_bitfield_expr_with_lowered_type (scalar_t__) ; 
 scalar_t__ type_promotes_to (scalar_t__) ; 

tree
perform_integral_promotions (tree expr)
{
  tree type;
  tree promoted_type;

  /* [conv.prom]

     If the bitfield has an enumerated type, it is treated as any
     other value of that type for promotion purposes.  */
  type = is_bitfield_expr_with_lowered_type (expr);
  if (!type || TREE_CODE (type) != ENUMERAL_TYPE)
    type = TREE_TYPE (expr);
  gcc_assert (INTEGRAL_OR_ENUMERATION_TYPE_P (type));
  promoted_type = type_promotes_to (type);
  if (type != promoted_type)
    expr = cp_convert (promoted_type, expr);
  return expr;
}