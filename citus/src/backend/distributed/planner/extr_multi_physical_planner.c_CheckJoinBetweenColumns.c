#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * args; } ;
typedef  TYPE_1__ OpExpr ;
typedef  scalar_t__ NodeTag ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ T_Var ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 scalar_t__ lsecond (int /*<<< orphan*/ *) ; 
 scalar_t__ nodeTag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strip_implicit_coercions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
CheckJoinBetweenColumns(OpExpr *joinClause)
{
	List *argumentList = joinClause->args;
	Node *leftArgument = (Node *) linitial(argumentList);
	Node *rightArgument = (Node *) lsecond(argumentList);
	Node *strippedLeftArgument = strip_implicit_coercions(leftArgument);
	Node *strippedRightArgument = strip_implicit_coercions(rightArgument);

	NodeTag leftArgumentType = nodeTag(strippedLeftArgument);
	NodeTag rightArgumentType = nodeTag(strippedRightArgument);

	if (leftArgumentType != T_Var || rightArgumentType != T_Var)
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot perform local joins that involve expressions"),
						errdetail("local joins can be performed between columns only")));
	}
}