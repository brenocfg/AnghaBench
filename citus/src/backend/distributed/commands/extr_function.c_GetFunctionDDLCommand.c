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
struct TYPE_4__ {int addCatalog; int /*<<< orphan*/  schemas; } ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  TYPE_1__ OverrideSearchPath ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* GetAggregateDDLCommand (int /*<<< orphan*/  const,int) ; 
 TYPE_1__* GetOverrideSearchPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/  const) ; 
 scalar_t__ PROKIND_AGGREGATE ; 
 int /*<<< orphan*/  PopOverrideSearchPath () ; 
 int /*<<< orphan*/  PushOverrideSearchPath (TYPE_1__*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 scalar_t__ get_func_prokind (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pg_get_functiondef ; 

char *
GetFunctionDDLCommand(const RegProcedure funcOid, bool useCreateOrReplace)
{
	OverrideSearchPath *overridePath = NULL;
	char *createFunctionSQL = NULL;

	if (get_func_prokind(funcOid) == PROKIND_AGGREGATE)
	{
		createFunctionSQL = GetAggregateDDLCommand(funcOid, useCreateOrReplace);
	}
	else
	{
		Datum sqlTextDatum = (Datum) 0;

		/*
		 * Set search_path to NIL so that all objects outside of pg_catalog will be
		 * schema-prefixed. pg_catalog will be added automatically when we call
		 * PushOverrideSearchPath(), since we set addCatalog to true;
		 */
		overridePath = GetOverrideSearchPath(CurrentMemoryContext);
		overridePath->schemas = NIL;
		overridePath->addCatalog = true;

		PushOverrideSearchPath(overridePath);
		sqlTextDatum = DirectFunctionCall1(pg_get_functiondef,
										   ObjectIdGetDatum(funcOid));
		createFunctionSQL = TextDatumGetCString(sqlTextDatum);

		/* revert back to original search_path */
		PopOverrideSearchPath();
	}

	return createFunctionSQL;
}