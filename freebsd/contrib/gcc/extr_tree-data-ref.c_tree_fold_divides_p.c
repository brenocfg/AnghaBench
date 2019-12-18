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
 int /*<<< orphan*/  tree_fold_gcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool 
tree_fold_divides_p (tree a, 
		     tree b)
{
  /* Determines whether (A == gcd (A, B)).  */
  return tree_int_cst_equal (a, tree_fold_gcd (a, b));
}