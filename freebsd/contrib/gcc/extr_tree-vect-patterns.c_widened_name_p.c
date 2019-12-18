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
typedef  int /*<<< orphan*/  stmt_vec_info ;
typedef  int /*<<< orphan*/  loop_vec_info ;
typedef  enum vect_def_type { ____Placeholder_vect_def_type } vect_def_type ;

/* Variables and functions */
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  STMT_VINFO_LOOP_VINFO (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int vect_constant_def ; 
 int vect_invariant_def ; 
 int /*<<< orphan*/  vect_is_simple_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int vect_loop_def ; 
 int /*<<< orphan*/  vinfo_for_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
widened_name_p (tree name, tree use_stmt, tree *half_type, tree *def_stmt)
{
  tree dummy;
  loop_vec_info loop_vinfo;
  stmt_vec_info stmt_vinfo;
  tree expr;
  tree type = TREE_TYPE (name);
  tree oprnd0;
  enum vect_def_type dt;
  tree def;

  stmt_vinfo = vinfo_for_stmt (use_stmt);
  loop_vinfo = STMT_VINFO_LOOP_VINFO (stmt_vinfo);

  if (!vect_is_simple_use (name, loop_vinfo, def_stmt, &def, &dt))
    return false;

  if (dt != vect_loop_def
      && dt != vect_invariant_def && dt != vect_constant_def)
    return false;

  if (! *def_stmt)
    return false;

  if (TREE_CODE (*def_stmt) != MODIFY_EXPR)
    return false;

  expr = TREE_OPERAND (*def_stmt, 1);
  if (TREE_CODE (expr) != NOP_EXPR)
    return false;

  oprnd0 = TREE_OPERAND (expr, 0);

  *half_type = TREE_TYPE (oprnd0);
  if (!INTEGRAL_TYPE_P (type) || !INTEGRAL_TYPE_P (*half_type)
      || (TYPE_UNSIGNED (type) != TYPE_UNSIGNED (*half_type))
      || (TYPE_PRECISION (type) < (TYPE_PRECISION (*half_type) * 2)))
    return false;

  if (!vect_is_simple_use (oprnd0, loop_vinfo, &dummy, &dummy, &dt))
    return false;

  if (dt != vect_invariant_def && dt != vect_constant_def
      && dt != vect_loop_def)
    return false;

  return true;
}