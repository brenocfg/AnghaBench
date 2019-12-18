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
struct TYPE_4__ {int addCatalog; void* schemas; } ;
typedef  TYPE_1__ OverrideSearchPath ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 TYPE_1__* GetOverrideSearchPath (int /*<<< orphan*/ ) ; 
 void* NIL ; 
 int /*<<< orphan*/  PopOverrideSearchPath () ; 
 int /*<<< orphan*/  PushOverrideSearchPath (TYPE_1__*) ; 
 char RELKIND_FOREIGN_TABLE ; 
 char* TableOwnerResetCommand (int /*<<< orphan*/ ) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 
 char* pg_get_extensiondef_string (int /*<<< orphan*/ ) ; 
 char* pg_get_serverdef_string (int /*<<< orphan*/ ) ; 
 char* pg_get_tablecolumnoptionsdef_string (int /*<<< orphan*/ ) ; 
 char* pg_get_tableschemadef_string (int /*<<< orphan*/ ,int) ; 

List *
GetTableCreationCommands(Oid relationId, bool includeSequenceDefaults)
{
	List *tableDDLEventList = NIL;
	char tableType = 0;
	char *tableSchemaDef = NULL;
	char *tableColumnOptionsDef = NULL;
	char *tableOwnerDef = NULL;

	/*
	 * Set search_path to NIL so that all objects outside of pg_catalog will be
	 * schema-prefixed. pg_catalog will be added automatically when we call
	 * PushOverrideSearchPath(), since we set addCatalog to true;
	 */
	OverrideSearchPath *overridePath = GetOverrideSearchPath(CurrentMemoryContext);
	overridePath->schemas = NIL;
	overridePath->addCatalog = true;
	PushOverrideSearchPath(overridePath);

	/* if foreign table, fetch extension and server definitions */
	tableType = get_rel_relkind(relationId);
	if (tableType == RELKIND_FOREIGN_TABLE)
	{
		char *extensionDef = pg_get_extensiondef_string(relationId);
		char *serverDef = pg_get_serverdef_string(relationId);

		if (extensionDef != NULL)
		{
			tableDDLEventList = lappend(tableDDLEventList, extensionDef);
		}
		tableDDLEventList = lappend(tableDDLEventList, serverDef);
	}

	/* fetch table schema and column option definitions */
	tableSchemaDef = pg_get_tableschemadef_string(relationId, includeSequenceDefaults);
	tableColumnOptionsDef = pg_get_tablecolumnoptionsdef_string(relationId);

	tableDDLEventList = lappend(tableDDLEventList, tableSchemaDef);
	if (tableColumnOptionsDef != NULL)
	{
		tableDDLEventList = lappend(tableDDLEventList, tableColumnOptionsDef);
	}

	tableOwnerDef = TableOwnerResetCommand(relationId);
	if (tableOwnerDef != NULL)
	{
		tableDDLEventList = lappend(tableDDLEventList, tableOwnerDef);
	}

	/* revert back to original search_path */
	PopOverrideSearchPath();

	return tableDDLEventList;
}