#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * CreatePolicyCommands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetTableCreationCommands (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * GetTableIndexAndConstraintCommands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetTableReplicaIdentityCommand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
GetTableDDLEvents(Oid relationId, bool includeSequenceDefaults)
{
	List *tableDDLEventList = NIL;
	List *tableCreationCommandList = NIL;
	List *indexAndConstraintCommandList = NIL;
	List *replicaIdentityEvents = NIL;
	List *policyCommands = NIL;

	tableCreationCommandList = GetTableCreationCommands(relationId,
														includeSequenceDefaults);
	tableDDLEventList = list_concat(tableDDLEventList, tableCreationCommandList);

	indexAndConstraintCommandList = GetTableIndexAndConstraintCommands(relationId);
	tableDDLEventList = list_concat(tableDDLEventList, indexAndConstraintCommandList);

	replicaIdentityEvents = GetTableReplicaIdentityCommand(relationId);
	tableDDLEventList = list_concat(tableDDLEventList, replicaIdentityEvents);

	policyCommands = CreatePolicyCommands(relationId);
	tableDDLEventList = list_concat(tableDDLEventList, policyCommands);

	return tableDDLEventList;
}