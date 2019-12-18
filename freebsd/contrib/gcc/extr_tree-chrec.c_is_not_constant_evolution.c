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
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
is_not_constant_evolution (tree cst)
{
  return (TREE_CODE (cst) == POLYNOMIAL_CHREC);
}