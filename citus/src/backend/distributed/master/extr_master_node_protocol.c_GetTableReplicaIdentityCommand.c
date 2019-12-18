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
 int /*<<< orphan*/ * NIL ; 
 char RELKIND_RELATION ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 
 char* pg_get_replica_identity_command (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
GetTableReplicaIdentityCommand(Oid relationId)
{
	List *replicaIdentityCreateCommandList = NIL;
	char *replicaIdentityCreateCommand = NULL;

	/*
	 * We skip non-relations because postgres does not support
	 * ALTER TABLE .. REPLICA IDENTITY on non-relations.
	 */
	char relationKind = get_rel_relkind(relationId);
	if (relationKind != RELKIND_RELATION)
	{
		return NIL;
	}

	replicaIdentityCreateCommand = pg_get_replica_identity_command(relationId);

	if (replicaIdentityCreateCommand)
	{
		replicaIdentityCreateCommandList = lappend(replicaIdentityCreateCommandList,
												   replicaIdentityCreateCommand);
	}

	return replicaIdentityCreateCommandList;
}