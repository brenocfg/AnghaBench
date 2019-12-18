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
typedef  int /*<<< orphan*/  loop_vec_info ;
typedef  enum vect_def_type { ____Placeholder_vect_def_type } vect_def_type ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARISON_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vect_is_simple_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool
vect_is_simple_cond (tree cond, loop_vec_info loop_vinfo)
{
  tree lhs, rhs;
  tree def;
  enum vect_def_type dt;

  if (!COMPARISON_CLASS_P (cond))
    return false;

  lhs = TREE_OPERAND (cond, 0);
  rhs = TREE_OPERAND (cond, 1);

  if (TREE_CODE (lhs) == SSA_NAME)
    {
      tree lhs_def_stmt = SSA_NAME_DEF_STMT (lhs);
      if (!vect_is_simple_use (lhs, loop_vinfo, &lhs_def_stmt, &def, &dt))
	return false;
    }
  else if (TREE_CODE (lhs) != INTEGER_CST && TREE_CODE (lhs) != REAL_CST)
    return false;

  if (TREE_CODE (rhs) == SSA_NAME)
    {
      tree rhs_def_stmt = SSA_NAME_DEF_STMT (rhs);
      if (!vect_is_simple_use (rhs, loop_vinfo, &rhs_def_stmt, &def, &dt))
	return false;
    }
  else if (TREE_CODE (rhs) != INTEGER_CST  && TREE_CODE (rhs) != REAL_CST)
    return false;

  return true;
}