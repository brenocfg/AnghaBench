#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  outerJoinQualifierList; int /*<<< orphan*/  baseQualifierList; } ;
typedef  TYPE_1__ QualifierWalkerContext ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  FromExpr ;

/* Variables and functions */
 int /*<<< orphan*/  ExtractFromExpressionWalker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc0 (int) ; 

List *
QualifierList(FromExpr *fromExpr)
{
	FromExpr *fromExprCopy = copyObject(fromExpr);
	QualifierWalkerContext *walkerContext = palloc0(sizeof(QualifierWalkerContext));
	List *qualifierList = NIL;

	ExtractFromExpressionWalker((Node *) fromExprCopy, walkerContext);
	qualifierList = list_concat(qualifierList, walkerContext->baseQualifierList);
	qualifierList = list_concat(qualifierList, walkerContext->outerJoinQualifierList);

	return qualifierList;
}