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
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
#define  POLYNOMIAL_CHREC 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_polynomial_chrec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree 
chrec_replace_initial_condition (tree chrec, 
				 tree init_cond)
{
  if (automatically_generated_chrec_p (chrec))
    return chrec;

  gcc_assert (chrec_type (chrec) == chrec_type (init_cond));

  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      return build_polynomial_chrec 
	(CHREC_VARIABLE (chrec),
	 chrec_replace_initial_condition (CHREC_LEFT (chrec), init_cond),
	 CHREC_RIGHT (chrec));
      
    default:
      return init_cond;
    }
}