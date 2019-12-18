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
typedef  int /*<<< orphan*/  int32 ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COERCE_EXPLICIT_CAST ; 
 int /*<<< orphan*/  COERCION_EXPLICIT ; 
 int /*<<< orphan*/ * coerce_to_target_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprTypmod (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Expr *
AddTypeConversion(Node *originalAggregate, Node *newExpression)
{
	Oid newTypeId = exprType(newExpression);
	Oid originalTypeId = exprType(originalAggregate);
	int32 originalTypeMod = exprTypmod(originalAggregate);
	Node *typeConvertedExpression = NULL;

	/* nothing to do if the two types are the same */
	if (originalTypeId == newTypeId)
	{
		return NULL;
	}

	/* otherwise, add a type conversion function */
	typeConvertedExpression = coerce_to_target_type(NULL, newExpression, newTypeId,
													originalTypeId, originalTypeMod,
													COERCION_EXPLICIT,
													COERCE_EXPLICIT_CAST, -1);
	Assert(typeConvertedExpression != NULL);
	return (Expr *) typeConvertedExpression;
}