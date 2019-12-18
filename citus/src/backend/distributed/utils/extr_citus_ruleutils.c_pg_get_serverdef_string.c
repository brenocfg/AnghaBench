#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  fdwname; } ;
struct TYPE_13__ {int /*<<< orphan*/  options; int /*<<< orphan*/ * serverversion; int /*<<< orphan*/ * servertype; int /*<<< orphan*/  servername; int /*<<< orphan*/  fdwid; } ;
struct TYPE_12__ {int /*<<< orphan*/  serverid; } ;
struct TYPE_11__ {char* data; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ForeignTable ;
typedef  TYPE_3__ ForeignServer ;
typedef  TYPE_4__ ForeignDataWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  AppendOptionListToString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* GetForeignDataWrapper (int /*<<< orphan*/ ) ; 
 TYPE_3__* GetForeignServer (int /*<<< orphan*/ ) ; 
 TYPE_2__* GetForeignTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_literal_cstr (int /*<<< orphan*/ *) ; 

char *
pg_get_serverdef_string(Oid tableRelationId)
{
	ForeignTable *foreignTable = GetForeignTable(tableRelationId);
	ForeignServer *server = GetForeignServer(foreignTable->serverid);
	ForeignDataWrapper *foreignDataWrapper = GetForeignDataWrapper(server->fdwid);

	StringInfoData buffer = { NULL, 0, 0, 0 };
	initStringInfo(&buffer);

	appendStringInfo(&buffer, "CREATE SERVER %s", quote_identifier(server->servername));
	if (server->servertype != NULL)
	{
		appendStringInfo(&buffer, " TYPE %s",
						 quote_literal_cstr(server->servertype));
	}
	if (server->serverversion != NULL)
	{
		appendStringInfo(&buffer, " VERSION %s",
						 quote_literal_cstr(server->serverversion));
	}

	appendStringInfo(&buffer, " FOREIGN DATA WRAPPER %s",
					 quote_identifier(foreignDataWrapper->fdwname));

	/* append server options, if any */
	AppendOptionListToString(&buffer, server->options);

	return (buffer.data);
}