#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_10__ {int /*<<< orphan*/  vartype; } ;
typedef  TYPE_1__ Var ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_11__ {scalar_t__ tdhasoid; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  BTORDER_PROC ; 
 int /*<<< orphan*/  BTREE_AM_OID ; 
 char DISTRIBUTE_BY_HASH ; 
 char DISTRIBUTE_BY_NONE ; 
 char DISTRIBUTE_BY_RANGE ; 
 scalar_t__ DistributionColumnUsesGeneratedStoredColumn (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureLocalTableEmptyIfNecessary (scalar_t__,char,int) ; 
 int /*<<< orphan*/  EnsureReplicationSettings (scalar_t__,char) ; 
 int /*<<< orphan*/  EnsureTableNotDistributed (scalar_t__) ; 
 int /*<<< orphan*/  ErrorIfUnsupportedConstraint (int /*<<< orphan*/ *,char,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ErrorIfUnsupportedPolicy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HASHSTANDARD_PROC ; 
 int /*<<< orphan*/  HASH_AM_OID ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  IsDistributedTable (scalar_t__) ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ PartitionParentOid (scalar_t__) ; 
 scalar_t__ PartitionTable (scalar_t__) ; 
 scalar_t__ PartitionedTable (scalar_t__) ; 
 TYPE_2__* RelationGetDescr (int /*<<< orphan*/ *) ; 
 char* RelationGetRelationName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationUsesHeapAccessMethodOrNone (int /*<<< orphan*/ *) ; 
 scalar_t__ RelationUsesIdentityColumns (TYPE_2__*) ; 
 scalar_t__ SupportFunctionForColumn (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdatatype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errhint (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 char* get_rel_name (scalar_t__) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * relation_open (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
EnsureRelationCanBeDistributed(Oid relationId, Var *distributionColumn,
							   char distributionMethod, uint32 colocationId,
							   char replicationModel, bool viaDeprecatedAPI)
{
	Relation relation = NULL;
	TupleDesc relationDesc = NULL;
	char *relationName = NULL;
	Oid parentRelationId = InvalidOid;

	EnsureTableNotDistributed(relationId);
	EnsureLocalTableEmptyIfNecessary(relationId, distributionMethod, viaDeprecatedAPI);
	EnsureReplicationSettings(InvalidOid, replicationModel);

	/* we assume callers took necessary locks */
	relation = relation_open(relationId, NoLock);
	relationDesc = RelationGetDescr(relation);
	relationName = RelationGetRelationName(relation);

	if (!RelationUsesHeapAccessMethodOrNone(relation))
	{
		ereport(ERROR, (errmsg(
							"cannot distribute relations using non-heap access methods")));
	}

#if PG_VERSION_NUM < 120000

	/* verify target relation does not use WITH (OIDS) PostgreSQL feature */
	if (relationDesc->tdhasoid)
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot distribute relation: %s", relationName),
						errdetail("Distributed relations must not specify the WITH "
								  "(OIDS) option in their definitions.")));
	}
#endif

	/* verify target relation does not use identity columns */
	if (RelationUsesIdentityColumns(relationDesc))
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot distribute relation: %s", relationName),
						errdetail("Distributed relations must not use GENERATED "
								  "... AS IDENTITY.")));
	}

	/* verify target relation is not distributed by a generated columns */
	if (distributionMethod != DISTRIBUTE_BY_NONE &&
		DistributionColumnUsesGeneratedStoredColumn(relationDesc, distributionColumn))
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot distribute relation: %s", relationName),
						errdetail("Distribution column must not use GENERATED ALWAYS "
								  "AS (...) STORED.")));
	}

	/* check for support function needed by specified partition method */
	if (distributionMethod == DISTRIBUTE_BY_HASH)
	{
		Oid hashSupportFunction = SupportFunctionForColumn(distributionColumn,
														   HASH_AM_OID,
														   HASHSTANDARD_PROC);
		if (hashSupportFunction == InvalidOid)
		{
			ereport(ERROR, (errcode(ERRCODE_UNDEFINED_FUNCTION),
							errmsg("could not identify a hash function for type %s",
								   format_type_be(distributionColumn->vartype)),
							errdatatype(distributionColumn->vartype),
							errdetail("Partition column types must have a hash function "
									  "defined to use hash partitioning.")));
		}
	}
	else if (distributionMethod == DISTRIBUTE_BY_RANGE)
	{
		Oid btreeSupportFunction = SupportFunctionForColumn(distributionColumn,
															BTREE_AM_OID, BTORDER_PROC);
		if (btreeSupportFunction == InvalidOid)
		{
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_FUNCTION),
					 errmsg("could not identify a comparison function for type %s",
							format_type_be(distributionColumn->vartype)),
					 errdatatype(distributionColumn->vartype),
					 errdetail("Partition column types must have a comparison function "
							   "defined to use range partitioning.")));
		}
	}

	if (PartitionTable(relationId))
	{
		parentRelationId = PartitionParentOid(relationId);
	}

	/* partitions cannot be distributed if their parent is not distributed */
	if (PartitionTable(relationId) && !IsDistributedTable(parentRelationId))
	{
		char *parentRelationName = get_rel_name(parentRelationId);

		ereport(ERROR, (errmsg("cannot distribute relation \"%s\" which is partition of "
							   "\"%s\"", relationName, parentRelationName),
						errdetail("Citus does not support distributing partitions "
								  "if their parent is not distributed table."),
						errhint("Distribute the partitioned table \"%s\" instead.",
								parentRelationName)));
	}

	/*
	 * These checks are mostly for partitioned tables not partitions because we prevent
	 * distributing partitions directly in the above check. However, partitions can still
	 * reach this point because, we call CreateDistributedTable for partitions if their
	 * parent table is distributed.
	 */
	if (PartitionedTable(relationId))
	{
		/* we cannot distribute partitioned tables with master_create_distributed_table */
		if (viaDeprecatedAPI)
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("distributing partitioned tables in only supported "
								   "with create_distributed_table UDF")));
		}

		/* distributing partitioned tables in only supported for hash-distribution */
		if (distributionMethod != DISTRIBUTE_BY_HASH)
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("distributing partitioned tables in only supported "
								   "for hash-distributed tables")));
		}

		/* we don't support distributing tables with multi-level partitioning */
		if (PartitionTable(relationId))
		{
			char *parentRelationName = get_rel_name(parentRelationId);

			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("distributing multi-level partitioned tables "
								   "is not supported"),
							errdetail("Relation \"%s\" is partitioned table itself and "
									  "it is also partition of relation \"%s\".",
									  relationName, parentRelationName)));
		}
	}

	ErrorIfUnsupportedConstraint(relation, distributionMethod, distributionColumn,
								 colocationId);


	ErrorIfUnsupportedPolicy(relation);
	relation_close(relation, NoLock);
}