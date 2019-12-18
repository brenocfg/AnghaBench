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
 scalar_t__ fold_non_dependent_expr (scalar_t__) ; 
 scalar_t__ integral_constant_value (scalar_t__) ; 

__attribute__((used)) static tree
fold_decl_constant_value (tree expr)
{
  tree const_expr = expr;
  do
    {
      expr = fold_non_dependent_expr (const_expr);
      const_expr = integral_constant_value (expr);
    }
  while (expr != const_expr);

  return expr;
}