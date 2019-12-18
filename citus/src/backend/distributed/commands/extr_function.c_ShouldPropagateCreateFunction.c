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
struct TYPE_3__ {int /*<<< orphan*/  replace; } ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ CreateFunctionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  EnableDependencyCreation ; 
 int /*<<< orphan*/ * GetObjectAddressFromParseTree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IsObjectDistributed (int /*<<< orphan*/  const*) ; 
 scalar_t__ creating_extension ; 

__attribute__((used)) static bool
ShouldPropagateCreateFunction(CreateFunctionStmt *stmt)
{
	const ObjectAddress *address = NULL;

	if (creating_extension)
	{
		/*
		 * extensions should be created separately on the workers, functions cascading
		 * from an extension should therefore not be propagated.
		 */
		return false;
	}

	if (!EnableDependencyCreation)
	{
		/*
		 * we are configured to disable object propagation, should not propagate anything
		 */
		return false;
	}

	if (!stmt->replace)
	{
		/*
		 * Since we only care for a replace of distributed functions if the statement is
		 * not a replace we are going to ignore.
		 */
		return false;
	}

	/*
	 * Even though its a replace we should accept an non-existing function, it will just
	 * not be distributed
	 */
	address = GetObjectAddressFromParseTree((Node *) stmt, true);
	if (!IsObjectDistributed(address))
	{
		/* do not propagate alter function for non-distributed functions */
		return false;
	}

	return true;
}