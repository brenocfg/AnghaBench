#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  fdwname; } ;
struct TYPE_12__ {int /*<<< orphan*/  fdwid; } ;
struct TYPE_11__ {int /*<<< orphan*/  serverid; } ;
struct TYPE_10__ {char* data; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ForeignTable ;
typedef  TYPE_3__ ForeignServer ;
typedef  TYPE_4__ ForeignDataWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  ForeignDataWrapperRelationId ; 
 TYPE_4__* GetForeignDataWrapper (int /*<<< orphan*/ ) ; 
 TYPE_3__* GetForeignServer (int /*<<< orphan*/ ) ; 
 TYPE_2__* GetForeignTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getExtensionOfObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* get_extension_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_extension_schema (int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_identifier (char*) ; 

char *
pg_get_extensiondef_string(Oid tableRelationId)
{
	ForeignTable *foreignTable = GetForeignTable(tableRelationId);
	ForeignServer *server = GetForeignServer(foreignTable->serverid);
	ForeignDataWrapper *foreignDataWrapper = GetForeignDataWrapper(server->fdwid);
	StringInfoData buffer = { NULL, 0, 0, 0 };

	Oid classId = ForeignDataWrapperRelationId;
	Oid objectId = server->fdwid;

	Oid extensionId = getExtensionOfObject(classId, objectId);
	if (OidIsValid(extensionId))
	{
		char *extensionName = get_extension_name(extensionId);
		Oid extensionSchemaId = get_extension_schema(extensionId);
		char *extensionSchema = get_namespace_name(extensionSchemaId);

		initStringInfo(&buffer);
		appendStringInfo(&buffer, "CREATE EXTENSION IF NOT EXISTS %s WITH SCHEMA %s",
						 quote_identifier(extensionName),
						 quote_identifier(extensionSchema));
	}
	else
	{
		ereport(NOTICE, (errmsg("foreign-data wrapper \"%s\" does not have an "
								"extension defined", foreignDataWrapper->fdwname)));
	}

	return (buffer.data);
}