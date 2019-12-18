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
typedef  int stmt_vec_info ;

/* Variables and functions */
 int /*<<< orphan*/  DOT_PROD_EXPR ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ MULT_EXPR ; 
 scalar_t__ PLUS_EXPR ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/ * SSA_NAME_DEF_STMT (int /*<<< orphan*/ *) ; 
 scalar_t__ STMT_VINFO_DEF_TYPE (int) ; 
 scalar_t__ STMT_VINFO_IN_PATTERN_P (int) ; 
 int /*<<< orphan*/ * STMT_VINFO_RELATED_STMT (int) ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ *) ; 
 int TYPE_PRECISION (int /*<<< orphan*/ *) ; 
 scalar_t__ WIDEN_MULT_EXPR ; 
 scalar_t__ WIDEN_SUM_EXPR ; 
 int /*<<< orphan*/ * build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_loop_def ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 
 scalar_t__ vect_reduction_def ; 
 int vinfo_for_stmt (int /*<<< orphan*/ *) ; 
 scalar_t__ widened_name_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static tree
vect_recog_dot_prod_pattern (tree last_stmt, tree *type_in, tree *type_out)
{
  tree stmt, expr;
  tree oprnd0, oprnd1;
  tree oprnd00, oprnd01;
  stmt_vec_info stmt_vinfo = vinfo_for_stmt (last_stmt);
  tree type, half_type;
  tree pattern_expr;
  tree prod_type;

  if (TREE_CODE (last_stmt) != MODIFY_EXPR)
    return NULL;

  expr = TREE_OPERAND (last_stmt, 1);
  type = TREE_TYPE (expr);

  /* Look for the following pattern 
          DX = (TYPE1) X;
          DY = (TYPE1) Y;
          DPROD = DX * DY; 
          DDPROD = (TYPE2) DPROD;
          sum_1 = DDPROD + sum_0;
     In which 
     - DX is double the size of X
     - DY is double the size of Y
     - DX, DY, DPROD all have the same type
     - sum is the same size of DPROD or bigger
     - sum has been recognized as a reduction variable.

     This is equivalent to:
       DPROD = X w* Y;          #widen mult
       sum_1 = DPROD w+ sum_0;  #widen summation
     or
       DPROD = X w* Y;          #widen mult
       sum_1 = DPROD + sum_0;   #summation
   */

  /* Starting from LAST_STMT, follow the defs of its uses in search
     of the above pattern.  */

  if (TREE_CODE (expr) != PLUS_EXPR)
    return NULL;

  if (STMT_VINFO_IN_PATTERN_P (stmt_vinfo))
    {
      /* Has been detected as widening-summation?  */

      stmt = STMT_VINFO_RELATED_STMT (stmt_vinfo);
      expr = TREE_OPERAND (stmt, 1);
      type = TREE_TYPE (expr);
      if (TREE_CODE (expr) != WIDEN_SUM_EXPR)
        return NULL;
      oprnd0 = TREE_OPERAND (expr, 0);
      oprnd1 = TREE_OPERAND (expr, 1);
      half_type = TREE_TYPE (oprnd0);
    }
  else
    {
      tree def_stmt;

      if (STMT_VINFO_DEF_TYPE (stmt_vinfo) != vect_reduction_def)
        return NULL;
      oprnd0 = TREE_OPERAND (expr, 0);
      oprnd1 = TREE_OPERAND (expr, 1);
      if (TYPE_MAIN_VARIANT (TREE_TYPE (oprnd0)) != TYPE_MAIN_VARIANT (type)
          || TYPE_MAIN_VARIANT (TREE_TYPE (oprnd1)) != TYPE_MAIN_VARIANT (type))
        return NULL;
      stmt = last_stmt;

      if (widened_name_p (oprnd0, stmt, &half_type, &def_stmt))
        {
          stmt = def_stmt;
          expr = TREE_OPERAND (stmt, 1);
          oprnd0 = TREE_OPERAND (expr, 0);
        }
      else
        half_type = type;
    }

  /* So far so good. Since last_stmt was detected as a (summation) reduction,
     we know that oprnd1 is the reduction variable (defined by a loop-header
     phi), and oprnd0 is an ssa-name defined by a stmt in the loop body.
     Left to check that oprnd0 is defined by a (widen_)mult_expr  */

  prod_type = half_type;
  stmt = SSA_NAME_DEF_STMT (oprnd0);
  gcc_assert (stmt);
  stmt_vinfo = vinfo_for_stmt (stmt);
  gcc_assert (stmt_vinfo);
  if (STMT_VINFO_DEF_TYPE (stmt_vinfo) != vect_loop_def)
    return NULL;
  expr = TREE_OPERAND (stmt, 1);
  if (TREE_CODE (expr) != MULT_EXPR)
    return NULL;
  if (STMT_VINFO_IN_PATTERN_P (stmt_vinfo))
    {
      /* Has been detected as a widening multiplication?  */

      stmt = STMT_VINFO_RELATED_STMT (stmt_vinfo);
      expr = TREE_OPERAND (stmt, 1);
      if (TREE_CODE (expr) != WIDEN_MULT_EXPR)
        return NULL;
      stmt_vinfo = vinfo_for_stmt (stmt);
      gcc_assert (stmt_vinfo);
      gcc_assert (STMT_VINFO_DEF_TYPE (stmt_vinfo) == vect_loop_def);
      oprnd00 = TREE_OPERAND (expr, 0);
      oprnd01 = TREE_OPERAND (expr, 1);
    }
  else
    {
      tree half_type0, half_type1;
      tree def_stmt;
      tree oprnd0, oprnd1;

      oprnd0 = TREE_OPERAND (expr, 0);
      oprnd1 = TREE_OPERAND (expr, 1);
      if (TYPE_MAIN_VARIANT (TREE_TYPE (oprnd0)) 
				!= TYPE_MAIN_VARIANT (prod_type)
          || TYPE_MAIN_VARIANT (TREE_TYPE (oprnd1)) 
				!= TYPE_MAIN_VARIANT (prod_type))
        return NULL;
      if (!widened_name_p (oprnd0, stmt, &half_type0, &def_stmt))
        return NULL;
      oprnd00 = TREE_OPERAND (TREE_OPERAND (def_stmt, 1), 0);
      if (!widened_name_p (oprnd1, stmt, &half_type1, &def_stmt))
        return NULL;
      oprnd01 = TREE_OPERAND (TREE_OPERAND (def_stmt, 1), 0);
      if (TYPE_MAIN_VARIANT (half_type0) != TYPE_MAIN_VARIANT (half_type1))
        return NULL;
      if (TYPE_PRECISION (prod_type) != TYPE_PRECISION (half_type0) * 2)
	return NULL;
    }

  half_type = TREE_TYPE (oprnd00);
  *type_in = half_type;
  *type_out = type;
  
  /* Pattern detected. Create a stmt to be used to replace the pattern: */
  pattern_expr = build3 (DOT_PROD_EXPR, type, oprnd00, oprnd01, oprnd1);
  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "vect_recog_dot_prod_pattern: detected: ");
      print_generic_expr (vect_dump, pattern_expr, TDF_SLIM);
    }
  return pattern_expr;
}