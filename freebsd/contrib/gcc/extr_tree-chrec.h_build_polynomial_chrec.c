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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ chrec_dont_know ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline tree 
build_polynomial_chrec (unsigned loop_num, 
			tree left, 
			tree right)
{
  if (left == chrec_dont_know
      || right == chrec_dont_know)
    return chrec_dont_know;

  gcc_assert (TREE_TYPE (left) == TREE_TYPE (right));

  return build3 (POLYNOMIAL_CHREC, TREE_TYPE (left), 
		 build_int_cst (NULL_TREE, loop_num), left, right);
}