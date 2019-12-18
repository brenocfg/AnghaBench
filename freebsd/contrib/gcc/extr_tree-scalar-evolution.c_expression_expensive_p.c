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
 scalar_t__ force_expr_to_var_cost (int /*<<< orphan*/ ) ; 
 scalar_t__ target_spill_cost ; 

__attribute__((used)) static bool
expression_expensive_p (tree expr)
{
  return force_expr_to_var_cost (expr) >= target_spill_cost;
}