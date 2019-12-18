#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* rd_rel; } ;
struct TYPE_10__ {scalar_t__ len; char* data; } ;
struct TYPE_9__ {char relreplident; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 char REPLICA_IDENTITY_FULL ; 
 char REPLICA_IDENTITY_INDEX ; 
 char REPLICA_IDENTITY_NOTHING ; 
 int /*<<< orphan*/  RelationGetReplicaIndex (TYPE_3__*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char*,...) ; 
 char* generate_qualified_relation_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 

char *
pg_get_replica_identity_command(Oid tableRelationId)
{
	Relation relation = NULL;
	StringInfo buf = makeStringInfo();
	char *relationName = NULL;
	char replicaIdentity = 0;

	relation = heap_open(tableRelationId, AccessShareLock);

	replicaIdentity = relation->rd_rel->relreplident;

	relationName = generate_qualified_relation_name(tableRelationId);

	if (replicaIdentity == REPLICA_IDENTITY_INDEX)
	{
		Oid indexId = RelationGetReplicaIndex(relation);

		if (OidIsValid(indexId))
		{
			appendStringInfo(buf, "ALTER TABLE %s REPLICA IDENTITY USING INDEX %s ",
							 relationName,
							 quote_identifier(get_rel_name(indexId)));
		}
	}
	else if (replicaIdentity == REPLICA_IDENTITY_NOTHING)
	{
		appendStringInfo(buf, "ALTER TABLE %s REPLICA IDENTITY NOTHING",
						 relationName);
	}
	else if (replicaIdentity == REPLICA_IDENTITY_FULL)
	{
		appendStringInfo(buf, "ALTER TABLE %s REPLICA IDENTITY FULL",
						 relationName);
	}

	heap_close(relation, AccessShareLock);

	return (buf->len > 0) ? buf->data : NULL;
}