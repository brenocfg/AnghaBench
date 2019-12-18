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
struct TYPE_3__ {int /*<<< orphan*/  objectType; } ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ AlterObjectDependsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AssertObjectTypeIsFunctional (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnableDependencyCreation ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IsObjectDistributed (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ creating_extension ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* getObjectIdentity (int /*<<< orphan*/  const*) ; 

List *
PlanAlterFunctionDependsStmt(AlterObjectDependsStmt *stmt, const char *queryString)
{
	const ObjectAddress *address = NULL;
	const char *functionName = NULL;

	AssertObjectTypeIsFunctional(stmt->objectType);

	if (creating_extension)
	{
		/*
		 * extensions should be created separately on the workers, types cascading from an
		 * extension should therefor not be propagated here.
		 */
		return NIL;
	}

	if (!EnableDependencyCreation)
	{
		/*
		 * we are configured to disable object propagation, should not propagate anything
		 */
		return NIL;
	}

	address = GetObjectAddressFromParseTree((Node *) stmt, true);
	if (!IsObjectDistributed(address))
	{
		return NIL;
	}

	/*
	 * Distributed objects should not start depending on an extension, this will break
	 * the dependency resolving mechanism we use to replicate distributed objects to new
	 * workers
	 */

	functionName = getObjectIdentity(address);
	ereport(ERROR, (errmsg("distrtibuted functions are not allowed to depend on an "
						   "extension"),
					errdetail("Function \"%s\" is already distributed. Functions from "
							  "extensions are expected to be created on the workers by "
							  "the extension they depend on.", functionName)));
}