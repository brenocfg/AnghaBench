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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  AppendShardIdToName (char**,scalar_t__) ; 
 scalar_t__ ExtractShardIdFromTableName (char*,int) ; 
 int GetLocalGroupId () ; 
 scalar_t__ INVALID_SHARD_ID ; 
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupShardRelation (scalar_t__,int) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrimaryNodeForGroup (int /*<<< orphan*/ ,int*) ; 
 char RELKIND_INDEX ; 
 int /*<<< orphan*/  RelationIsVisible (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 scalar_t__ get_rel_namespace (int /*<<< orphan*/ ) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * try_relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
RelationIsAKnownShard(Oid shardRelationId, bool onlySearchPath)
{
	int localGroupId = -1;
	char *shardRelationName = NULL;
	char *generatedRelationName = NULL;
	bool missingOk = true;
	uint64 shardId = INVALID_SHARD_ID;
	Oid relationId = InvalidOid;
	char relKind = '\0';
	Relation relation = NULL;

	if (!OidIsValid(shardRelationId))
	{
		/* we cannot continue without a valid Oid */
		return false;
	}

	localGroupId = GetLocalGroupId();
	if (localGroupId == 0)
	{
		bool coordinatorIsKnown = false;
		PrimaryNodeForGroup(0, &coordinatorIsKnown);

		if (!coordinatorIsKnown)
		{
			/*
			 * We're not interested in shards in the coordinator
			 * or non-mx worker nodes, unless the coordinator is
			 * in pg_dist_node.
			 */
			return false;
		}
	}

	relation = try_relation_open(shardRelationId, AccessShareLock);
	if (relation == NULL)
	{
		return false;
	}
	relation_close(relation, NoLock);

	/* we're not interested in the relations that are not in the search path */
	if (!RelationIsVisible(shardRelationId) && onlySearchPath)
	{
		return false;
	}

	/*
	 * If the input relation is an index we simply replace the
	 * relationId with the corresponding relation to hide indexes
	 * as well.
	 */
	relKind = get_rel_relkind(shardRelationId);
	if (relKind == RELKIND_INDEX)
	{
		shardRelationId = IndexGetRelation(shardRelationId, false);
	}

	/* get the shard's relation name */
	shardRelationName = get_rel_name(shardRelationId);

	shardId = ExtractShardIdFromTableName(shardRelationName, missingOk);
	if (shardId == INVALID_SHARD_ID)
	{
		/*
		 * The format of the table name does not align with
		 * our shard name definition.
		 */
		return false;
	}

	/* try to get the relation id */
	relationId = LookupShardRelation(shardId, true);
	if (!OidIsValid(relationId))
	{
		/* there is no such relation */
		return false;
	}

	/* verify that their namespaces are the same */
	if (get_rel_namespace(shardRelationId) != get_rel_namespace(relationId))
	{
		return false;
	}

	/*
	 * Now get the relation name and append the shardId to it. We need
	 * to do that because otherwise a local table with a valid shardId
	 * appended to its name could be misleading.
	 */
	generatedRelationName = get_rel_name(relationId);
	AppendShardIdToName(&generatedRelationName, shardId);
	if (strncmp(shardRelationName, generatedRelationName, NAMEDATALEN) == 0)
	{
		/* we found the distributed table that the input shard belongs to */
		return true;
	}

	return false;
}