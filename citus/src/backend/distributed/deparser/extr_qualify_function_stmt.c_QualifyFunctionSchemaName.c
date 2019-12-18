#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  proname; int /*<<< orphan*/  pronamespace; } ;
struct TYPE_5__ {int /*<<< orphan*/  objname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectWithArgs ;
typedef  int /*<<< orphan*/  ObjectType ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupFuncWithArgs (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 char* pstrdup (char*) ; 

void
QualifyFunctionSchemaName(ObjectWithArgs *func, ObjectType type)
{
	char *schemaName = NULL;
	char *functionName = NULL;
	Oid funcid = InvalidOid;
	HeapTuple proctup;

	funcid = LookupFuncWithArgs(type, func, true);
	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));

	/*
	 * We can not qualify the function if the catalogs do not have any records.
	 *
	 * e.g. DROP FUNC IF EXISTS non_existent_func() do not result in a valid heap tuple
	 */
	if (HeapTupleIsValid(proctup))
	{
		Form_pg_proc procform;

		procform = (Form_pg_proc) GETSTRUCT(proctup);
		schemaName = get_namespace_name(procform->pronamespace);
		functionName = NameStr(procform->proname);
		functionName = pstrdup(functionName); /* we release the tuple before used */

		ReleaseSysCache(proctup);

		/* update the function using the schema name */
		func->objname = list_make2(makeString(schemaName), makeString(functionName));
	}
}