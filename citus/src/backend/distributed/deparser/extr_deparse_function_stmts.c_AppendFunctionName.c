#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pronamespace; int /*<<< orphan*/  proname; } ;
struct TYPE_9__ {int /*<<< orphan*/  objargs; int /*<<< orphan*/  args_unspecified; int /*<<< orphan*/  objname; } ;
struct TYPE_8__ {int addCatalog; int /*<<< orphan*/  schemas; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ OverrideSearchPath ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectWithArgs ;
typedef  int /*<<< orphan*/  ObjectType ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_proc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DeconstructQualifiedName (int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetOverrideSearchPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupFuncWithArgs (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  PopOverrideSearchPath () ; 
 int /*<<< orphan*/  PushOverrideSearchPath (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 char* TypeNameListToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_get_function_identity_arguments ; 
 char* pstrdup (char*) ; 
 char* quote_qualified_identifier (char*,char*) ; 

__attribute__((used)) static void
AppendFunctionName(StringInfo buf, ObjectWithArgs *func, ObjectType objtype)
{
	Oid funcid = InvalidOid;
	HeapTuple proctup;
	char *functionName = NULL;
	char *schemaName = NULL;
	char *qualifiedFunctionName;

	funcid = LookupFuncWithArgs(objtype, func, true);
	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));

	if (!HeapTupleIsValid(proctup))
	{
		/*
		 * DROP FUNCTION IF EXISTS absent_function arrives here
		 *
		 * There is no namespace associated with the nonexistent function,
		 * thus we return the function name as it is provided
		 */
		DeconstructQualifiedName(func->objname, &schemaName, &functionName);
	}
	else
	{
		Form_pg_proc procform;

		procform = (Form_pg_proc) GETSTRUCT(proctup);
		functionName = NameStr(procform->proname);
		functionName = pstrdup(functionName); /* we release the tuple before used */
		schemaName = get_namespace_name(procform->pronamespace);

		ReleaseSysCache(proctup);
	}

	qualifiedFunctionName = quote_qualified_identifier(schemaName, functionName);
	appendStringInfoString(buf, qualifiedFunctionName);

	if (OidIsValid(funcid))
	{
		/*
		 * If the function exists we want to use pg_get_function_identity_arguments to
		 * serialize its canonical arguments
		 */
		OverrideSearchPath *overridePath = NULL;
		Datum sqlTextDatum = 0;
		const char *args = NULL;

		/*
		 * Set search_path to NIL so that all objects outside of pg_catalog will be
		 * schema-prefixed. pg_catalog will be added automatically when we call
		 * PushOverrideSearchPath(), since we set addCatalog to true;
		 */
		overridePath = GetOverrideSearchPath(CurrentMemoryContext);
		overridePath->schemas = NIL;
		overridePath->addCatalog = true;

		PushOverrideSearchPath(overridePath);

		sqlTextDatum = DirectFunctionCall1(pg_get_function_identity_arguments,
										   ObjectIdGetDatum(funcid));

		/* revert back to original search_path */
		PopOverrideSearchPath();

		args = TextDatumGetCString(sqlTextDatum);
		appendStringInfo(buf, "(%s)", args);
	}
	else if (!func->args_unspecified)
	{
		/*
		 * The function is not found, but there is an argument list specified, this has
		 * some known issues with the "any" type. However this is mostly a bug in
		 * postgres' TypeNameListToString. For now the best we can do until we understand
		 * the underlying cause better.
		 */
		const char *args = NULL;

		args = TypeNameListToString(func->objargs);
		appendStringInfo(buf, "(%s)", args);
	}

	/*
	 * If the type is not found, and no argument list given we don't append anything here.
	 * This will cause mostly the same sql as the original statement.
	 */
}