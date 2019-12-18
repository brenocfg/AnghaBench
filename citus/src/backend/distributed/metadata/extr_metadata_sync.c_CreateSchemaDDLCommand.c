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
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_SCHEMA_COMMAND ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char* SchemaOwnerName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,char const*,char const*) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 char* quote_identifier (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

char *
CreateSchemaDDLCommand(Oid schemaId)
{
	char *schemaName = get_namespace_name(schemaId);
	StringInfo schemaNameDef = NULL;
	const char *ownerName = NULL;
	const char *quotedSchemaName = NULL;

	if (strncmp(schemaName, "public", NAMEDATALEN) == 0)
	{
		return NULL;
	}

	schemaNameDef = makeStringInfo();
	quotedSchemaName = quote_identifier(schemaName);
	ownerName = quote_identifier(SchemaOwnerName(schemaId));
	appendStringInfo(schemaNameDef, CREATE_SCHEMA_COMMAND, quotedSchemaName, ownerName);

	return schemaNameDef->data;
}