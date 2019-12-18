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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  CreateFunctionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsureSequentialModeForFunctionDDL () ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ShouldPropagateCreateFunction (int /*<<< orphan*/ *) ; 

List *
PlanCreateFunctionStmt(CreateFunctionStmt *stmt, const char *queryString)
{
	if (!ShouldPropagateCreateFunction(stmt))
	{
		return NIL;
	}

	EnsureCoordinator();

	EnsureSequentialModeForFunctionDDL();

	/*
	 * ddl jobs will be generated during the Processing phase as we need the function to
	 * be updated in the catalog to get its sql representation
	 */
	return NIL;
}