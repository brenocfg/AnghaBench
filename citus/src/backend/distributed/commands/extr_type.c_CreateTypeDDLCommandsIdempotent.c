#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ classId; int /*<<< orphan*/  objectId; } ;
struct TYPE_8__ {void* data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ALTER_TYPE_OWNER_COMMAND ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * CreateTypeStmtByObjectAddress (TYPE_2__ const*) ; 
 char* DeparseTreeNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTypeOwner (int /*<<< orphan*/ ) ; 
 char* GetUserNameFromId (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ TypeRelationId ; 
 char* WrapCreateOrReplace (char const*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getObjectIdentity (TYPE_2__ const*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  quote_identifier (char const*) ; 
 scalar_t__ type_is_array (int /*<<< orphan*/ ) ; 

List *
CreateTypeDDLCommandsIdempotent(const ObjectAddress *typeAddress)
{
	List *ddlCommands = NIL;
	const char *ddlCommand = NULL;
	Node *stmt = NULL;
	StringInfoData buf = { 0 };
	const char *username = NULL;

	Assert(typeAddress->classId == TypeRelationId);

	if (type_is_array(typeAddress->objectId))
	{
		/*
		 * array types cannot be created on their own, but could be a direct dependency of
		 * a table. In that case they are on the dependency graph and tried to be created.
		 *
		 * By returning an empty list we will not send any commands to create this type.
		 */
		return NIL;
	}

	stmt = CreateTypeStmtByObjectAddress(typeAddress);

	/* capture ddl command for recreation and wrap in create if not exists construct */
	ddlCommand = DeparseTreeNode(stmt);
	ddlCommand = WrapCreateOrReplace(ddlCommand);
	ddlCommands = lappend(ddlCommands, (void *) ddlCommand);

	/* add owner ship change so the creation command can be run as a different user */
	username = GetUserNameFromId(GetTypeOwner(typeAddress->objectId), false);
	initStringInfo(&buf);
	appendStringInfo(&buf, ALTER_TYPE_OWNER_COMMAND, getObjectIdentity(typeAddress),
					 quote_identifier(username));
	ddlCommands = lappend(ddlCommands, buf.data);

	return ddlCommands;
}