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
 scalar_t__ fold (scalar_t__) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 

__attribute__((used)) static tree
fully_constant_expression (tree t)
{
  tree folded;
  folded = fold (t);
  if (folded && is_gimple_min_invariant (folded))
    return folded;
  return t;
}