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
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  CompositeTypeStmt ;

/* Variables and functions */
 int /*<<< orphan*/  EnsureDependenciesExistsOnAllNodes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MarkObjectDistributed (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ShouldPropagateTypeCreate () ; 

void
ProcessCompositeTypeStmt(CompositeTypeStmt *stmt, const char *queryString)
{
	const ObjectAddress *typeAddress = NULL;

	/* same check we perform during planning of the statement */
	if (!ShouldPropagateTypeCreate())
	{
		return;
	}

	/*
	 * find object address of the just created object, because the type has been created
	 * locally it can't be missing
	 */
	typeAddress = GetObjectAddressFromParseTree((Node *) stmt, false);
	EnsureDependenciesExistsOnAllNodes(typeAddress);

	MarkObjectDistributed(typeAddress);
}