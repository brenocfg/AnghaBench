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
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ convert_to_integer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ is_bitfield_expr_with_lowered_type (scalar_t__) ; 

tree
convert_bitfield_to_declared_type (tree expr)
{
  tree bitfield_type;

  bitfield_type = is_bitfield_expr_with_lowered_type (expr);
  if (bitfield_type)
    expr = convert_to_integer (TYPE_MAIN_VARIANT (bitfield_type),
			       expr);
  return expr;
}