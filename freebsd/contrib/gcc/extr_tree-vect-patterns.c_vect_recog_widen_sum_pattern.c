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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  stmt_vec_info ;

/* Variables and functions */
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ PLUS_EXPR ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 scalar_t__ STMT_VINFO_DEF_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIDEN_SUM_EXPR ; 
 int /*<<< orphan*/ * build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 
 scalar_t__ vect_reduction_def ; 
 int /*<<< orphan*/  vinfo_for_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widened_name_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static tree
vect_recog_widen_sum_pattern (tree last_stmt, tree *type_in, tree *type_out)
{
  tree stmt, expr;
  tree oprnd0, oprnd1;
  stmt_vec_info stmt_vinfo = vinfo_for_stmt (last_stmt);
  tree type, half_type;
  tree pattern_expr;

  if (TREE_CODE (last_stmt) != MODIFY_EXPR)
    return NULL;

  expr = TREE_OPERAND (last_stmt, 1);
  type = TREE_TYPE (expr);

  /* Look for the following pattern
          DX = (TYPE) X;
          sum_1 = DX + sum_0;
     In which DX is at least double the size of X, and sum_1 has been
     recognized as a reduction variable.
   */

  /* Starting from LAST_STMT, follow the defs of its uses in search
     of the above pattern.  */

  if (TREE_CODE (expr) != PLUS_EXPR)
    return NULL;

  if (STMT_VINFO_DEF_TYPE (stmt_vinfo) != vect_reduction_def)
    return NULL;

  oprnd0 = TREE_OPERAND (expr, 0);
  oprnd1 = TREE_OPERAND (expr, 1);
  if (TYPE_MAIN_VARIANT (TREE_TYPE (oprnd0)) != TYPE_MAIN_VARIANT (type)
      || TYPE_MAIN_VARIANT (TREE_TYPE (oprnd1)) != TYPE_MAIN_VARIANT (type))
    return NULL;

  /* So far so good. Since last_stmt was detected as a (summation) reduction,
     we know that oprnd1 is the reduction variable (defined by a loop-header
     phi), and oprnd0 is an ssa-name defined by a stmt in the loop body.
     Left to check that oprnd0 is defined by a cast from type 'type' to type
     'TYPE'.  */

  if (!widened_name_p (oprnd0, last_stmt, &half_type, &stmt))
    return NULL;

  oprnd0 = TREE_OPERAND (TREE_OPERAND (stmt, 1), 0);
  *type_in = half_type;
  *type_out = type;

  /* Pattern detected. Create a stmt to be used to replace the pattern: */
  pattern_expr = build2 (WIDEN_SUM_EXPR, type, oprnd0, oprnd1);
  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "vect_recog_widen_sum_pattern: detected: ");
      print_generic_expr (vect_dump, pattern_expr, TDF_SLIM);
    }
  return pattern_expr;
}