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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ MULT_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ RDIV_EXPR ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst1 ; 
 int /*<<< orphan*/  fold_build2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_arithmetic (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
distribute_real_division (enum tree_code code, tree type, tree arg0, tree arg1)
{
  bool mul0 = TREE_CODE (arg0) == MULT_EXPR;
  bool mul1 = TREE_CODE (arg1) == MULT_EXPR;

  /* (A / C) +- (B / C) -> (A +- B) / C.  */
  if (mul0 == mul1
      && operand_equal_p (TREE_OPERAND (arg0, 1),
		       TREE_OPERAND (arg1, 1), 0))
    return fold_build2 (mul0 ? MULT_EXPR : RDIV_EXPR, type,
			fold_build2 (code, type,
				     TREE_OPERAND (arg0, 0),
				     TREE_OPERAND (arg1, 0)),
			TREE_OPERAND (arg0, 1));

  /* (A / C1) +- (A / C2) -> A * (1 / C1 +- 1 / C2).  */
  if (operand_equal_p (TREE_OPERAND (arg0, 0),
		       TREE_OPERAND (arg1, 0), 0)
      && TREE_CODE (TREE_OPERAND (arg0, 1)) == REAL_CST
      && TREE_CODE (TREE_OPERAND (arg1, 1)) == REAL_CST)
    {
      REAL_VALUE_TYPE r0, r1;
      r0 = TREE_REAL_CST (TREE_OPERAND (arg0, 1));
      r1 = TREE_REAL_CST (TREE_OPERAND (arg1, 1));
      if (!mul0)
	real_arithmetic (&r0, RDIV_EXPR, &dconst1, &r0);
      if (!mul1)
        real_arithmetic (&r1, RDIV_EXPR, &dconst1, &r1);
      real_arithmetic (&r0, code, &r0, &r1);
      return fold_build2 (MULT_EXPR, type,
			  TREE_OPERAND (arg0, 0),
			  build_real (type, r0));
    }

  return NULL_TREE;
}