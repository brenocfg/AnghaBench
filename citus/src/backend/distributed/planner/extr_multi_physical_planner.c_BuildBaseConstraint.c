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
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  OpExpr ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  BTGreaterEqualStrategyNumber ; 
 int /*<<< orphan*/  BTLessEqualStrategyNumber ; 
 int /*<<< orphan*/ * MakeOpExpression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_and_qual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Node *
BuildBaseConstraint(Var *column)
{
	Node *baseConstraint = NULL;
	OpExpr *lessThanExpr = NULL;
	OpExpr *greaterThanExpr = NULL;

	/* Build these expressions with only one argument for now */
	lessThanExpr = MakeOpExpression(column, BTLessEqualStrategyNumber);
	greaterThanExpr = MakeOpExpression(column, BTGreaterEqualStrategyNumber);

	/* Build base constaint as an and of two qual conditions */
	baseConstraint = make_and_qual((Node *) lessThanExpr, (Node *) greaterThanExpr);

	return baseConstraint;
}