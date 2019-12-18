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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ BINARY_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CALL_EXPR ; 
 scalar_t__ COMPARISON_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REFERENCE_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNARY_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ can_value_number_call (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
can_value_number_operation (tree op)
{
  return UNARY_CLASS_P (op)
    || BINARY_CLASS_P (op)
    || COMPARISON_CLASS_P (op)
    || REFERENCE_CLASS_P (op)
    || (TREE_CODE (op) == CALL_EXPR
	&& can_value_number_call (op));
}