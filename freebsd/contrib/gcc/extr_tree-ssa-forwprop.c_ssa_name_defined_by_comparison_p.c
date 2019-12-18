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
 int COMPARISON_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
ssa_name_defined_by_comparison_p (tree var)
{
  tree def = SSA_NAME_DEF_STMT (var);

  if (TREE_CODE (def) == MODIFY_EXPR)
    {
      tree rhs = TREE_OPERAND (def, 1);
      return COMPARISON_CLASS_P (rhs);
    }

  return 0;
}