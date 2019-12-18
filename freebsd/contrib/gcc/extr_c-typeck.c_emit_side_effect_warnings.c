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
 scalar_t__ EXPR_HAS_LOCATION (scalar_t__) ; 
 int /*<<< orphan*/ * EXPR_LOCUS (scalar_t__) ; 
 int /*<<< orphan*/  TREE_NO_WARNING (scalar_t__) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  warn_if_unused_value (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_unused_value ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
emit_side_effect_warnings (tree expr)
{
  if (expr == error_mark_node)
    ;
  else if (!TREE_SIDE_EFFECTS (expr))
    {
      if (!VOID_TYPE_P (TREE_TYPE (expr)) && !TREE_NO_WARNING (expr))
	warning (0, "%Hstatement with no effect",
		 EXPR_HAS_LOCATION (expr) ? EXPR_LOCUS (expr) : &input_location);
    }
  else if (warn_unused_value)
    warn_if_unused_value (expr, input_location);
}