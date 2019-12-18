#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  paramkind; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_1__ Param ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Const ; 
 int /*<<< orphan*/  FindNodeCheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsVarNode ; 
 int /*<<< orphan*/  PARAM_SUBLINK ; 
 int /*<<< orphan*/  QTW_DONT_COPY_QUERY ; 
#define  T_ArrayCoerceExpr 139 
#define  T_CoerceToDomain 138 
#define  T_CoerceViaIO 137 
#define  T_DistinctExpr 136 
#define  T_FuncExpr 135 
#define  T_NullIfExpr 134 
#define  T_OpExpr 133 
#define  T_Param 132 
#define  T_Query 131 
#define  T_RelabelType 130 
#define  T_RowCompareExpr 129 
#define  T_ScalarArrayOpExpr 128 
 scalar_t__ citus_evaluate_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprCollation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprTypmod (int /*<<< orphan*/ *) ; 
 scalar_t__ expression_tree_mutator (int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 
 scalar_t__ query_tree_mutator (int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Node *
PartiallyEvaluateExpression(Node *expression, PlanState *planState)
{
	if (expression == NULL || IsA(expression, Const))
	{
		return expression;
	}

	switch (nodeTag(expression))
	{
		case T_Param:
		{
			Param *param = (Param *) expression;
			if (param->paramkind == PARAM_SUBLINK)
			{
				/* ExecInitExpr cannot handle PARAM_SUBLINK */
				return expression;
			}
		}

		/* fallthrough */

		case T_FuncExpr:
		case T_OpExpr:
		case T_DistinctExpr:
		case T_NullIfExpr:
		case T_CoerceViaIO:
		case T_ArrayCoerceExpr:
		case T_ScalarArrayOpExpr:
		case T_RowCompareExpr:
		case T_RelabelType:
		case T_CoerceToDomain:
		{
			if (FindNodeCheck(expression, IsVarNode))
			{
				return (Node *) expression_tree_mutator(expression,
														PartiallyEvaluateExpression,
														planState);
			}

			return (Node *) citus_evaluate_expr((Expr *) expression,
												exprType(expression),
												exprTypmod(expression),
												exprCollation(expression),
												planState);
		}

		case T_Query:
		{
			return (Node *) query_tree_mutator((Query *) expression,
											   PartiallyEvaluateExpression,
											   planState, QTW_DONT_COPY_QUERY);
		}

		default:
		{
			return (Node *) expression_tree_mutator(expression,
													PartiallyEvaluateExpression,
													planState);
		}
	}

	return expression;
}