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
 int /*<<< orphan*/  CHREC_VARIABLE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
#define  POLYNOMIAL_CHREC 128 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ initial_condition_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 

unsigned 
nb_vars_in_chrec (tree chrec)
{
  if (chrec == NULL_TREE)
    return 0;

  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      return 1 + nb_vars_in_chrec 
	(initial_condition_in_loop_num (chrec, CHREC_VARIABLE (chrec)));

    default:
      return 0;
    }
}