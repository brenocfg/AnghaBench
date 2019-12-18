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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_FOREIGN_TABLE_COMMAND ; 
 int /*<<< orphan*/  DROP_REGULAR_TABLE_COMMAND ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * GetTableCreationCommands (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NIL ; 
 char RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RegularTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 char* quote_qualified_identifier (char const*,char const*) ; 

__attribute__((used)) static List *
RecreateTableDDLCommandList(Oid relationId)
{
	const char *relationName = get_rel_name(relationId);
	Oid relationSchemaId = get_rel_namespace(relationId);
	const char *relationSchemaName = get_namespace_name(relationSchemaId);
	const char *qualifiedRelationName = quote_qualified_identifier(relationSchemaName,
																   relationName);

	StringInfo dropCommand = makeStringInfo();
	List *createCommandList = NIL;
	List *dropCommandList = NIL;
	List *recreateCommandList = NIL;
	char relationKind = get_rel_relkind(relationId);
	bool includeSequenceDefaults = false;

	/* build appropriate DROP command based on relation kind */
	if (RegularTable(relationId))
	{
		appendStringInfo(dropCommand, DROP_REGULAR_TABLE_COMMAND,
						 qualifiedRelationName);
	}
	else if (relationKind == RELKIND_FOREIGN_TABLE)
	{
		appendStringInfo(dropCommand, DROP_FOREIGN_TABLE_COMMAND,
						 qualifiedRelationName);
	}
	else
	{
		ereport(ERROR, (errcode(ERRCODE_WRONG_OBJECT_TYPE),
						errmsg("repair target is not a regular, foreign or partitioned "
							   "table")));
	}

	dropCommandList = list_make1(dropCommand->data);
	createCommandList = GetTableCreationCommands(relationId, includeSequenceDefaults);
	recreateCommandList = list_concat(dropCommandList, createCommandList);

	return recreateCommandList;
}