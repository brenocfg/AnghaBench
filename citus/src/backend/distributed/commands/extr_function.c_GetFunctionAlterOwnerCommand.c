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
struct TYPE_10__ {scalar_t__ prokind; int /*<<< orphan*/  proowner; } ;
struct TYPE_9__ {int addCatalog; int /*<<< orphan*/  schemas; } ;
struct TYPE_8__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  TYPE_2__ OverrideSearchPath ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_proc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_2__* GetOverrideSearchPath (int /*<<< orphan*/ ) ; 
 char* GetUserNameFromId (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  PROCOID ; 
 scalar_t__ PROKIND_AGGREGATE ; 
 scalar_t__ PROKIND_PROCEDURE ; 
 int /*<<< orphan*/  PopOverrideSearchPath () ; 
 int /*<<< orphan*/  PushOverrideSearchPath (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/  const) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_identifier (char*) ; 
 int /*<<< orphan*/  regprocedureout ; 

__attribute__((used)) static char *
GetFunctionAlterOwnerCommand(const RegProcedure funcOid)
{
	HeapTuple proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcOid));
	StringInfo alterCommand = makeStringInfo();
	char *kindString = "FUNCTION";
	Oid procOwner = InvalidOid;

	char *functionSignature = NULL;
	char *functionOwner = NULL;

	OverrideSearchPath *overridePath = NULL;
	Datum functionSignatureDatum = 0;

	if (HeapTupleIsValid(proctup))
	{
		Form_pg_proc procform;

		procform = (Form_pg_proc) GETSTRUCT(proctup);

		procOwner = procform->proowner;

		if (procform->prokind == PROKIND_PROCEDURE)
		{
			kindString = "PROCEDURE";
		}
		else if (procform->prokind == PROKIND_AGGREGATE)
		{
			kindString = "AGGREGATE";
		}

		ReleaseSysCache(proctup);
	}
	else if (!OidIsValid(funcOid) || !HeapTupleIsValid(proctup))
	{
		ereport(ERROR, (errmsg("cannot find function with oid: %d", funcOid)));
	}

	/*
	 * Set search_path to NIL so that all objects outside of pg_catalog will be
	 * schema-prefixed. pg_catalog will be added automatically when we call
	 * PushOverrideSearchPath(), since we set addCatalog to true;
	 */
	overridePath = GetOverrideSearchPath(CurrentMemoryContext);
	overridePath->schemas = NIL;
	overridePath->addCatalog = true;

	PushOverrideSearchPath(overridePath);

	/*
	 * If the function exists we want to use pg_get_function_identity_arguments to
	 * serialize its canonical arguments
	 */
	functionSignatureDatum =
		DirectFunctionCall1(regprocedureout, ObjectIdGetDatum(funcOid));

	/* revert back to original search_path */
	PopOverrideSearchPath();

	/* regprocedureout returns cstring */
	functionSignature = DatumGetCString(functionSignatureDatum);

	functionOwner = GetUserNameFromId(procOwner, false);

	appendStringInfo(alterCommand, "ALTER %s %s OWNER TO %s;",
					 kindString,
					 functionSignature,
					 quote_identifier(functionOwner));

	return alterCommand->data;
}