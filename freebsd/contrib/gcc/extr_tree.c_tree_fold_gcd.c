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
 int /*<<< orphan*/  FLOOR_MOD_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 int tree_int_cst_sgn (int /*<<< orphan*/ ) ; 

tree
tree_fold_gcd (tree a, tree b)
{
  tree a_mod_b;
  tree type = TREE_TYPE (a);

  gcc_assert (TREE_CODE (a) == INTEGER_CST);
  gcc_assert (TREE_CODE (b) == INTEGER_CST);

  if (integer_zerop (a))
    return b;

  if (integer_zerop (b))
    return a;

  if (tree_int_cst_sgn (a) == -1)
    a = fold_build2 (MULT_EXPR, type, a,
		     build_int_cst (type, -1));

  if (tree_int_cst_sgn (b) == -1)
    b = fold_build2 (MULT_EXPR, type, b,
		     build_int_cst (type, -1));

  while (1)
    {
      a_mod_b = fold_build2 (FLOOR_MOD_EXPR, type, a, b);

      if (!TREE_INT_CST_LOW (a_mod_b)
	  && !TREE_INT_CST_HIGH (a_mod_b))
	return b;

      a = b;
      b = a_mod_b;
    }
}