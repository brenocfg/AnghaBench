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
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 

tree 
initial_condition (tree chrec)
{
  if (automatically_generated_chrec_p (chrec))
    return chrec;
  
  if (TREE_CODE (chrec) == POLYNOMIAL_CHREC)
    return initial_condition (CHREC_LEFT (chrec));
  else
    return chrec;
}