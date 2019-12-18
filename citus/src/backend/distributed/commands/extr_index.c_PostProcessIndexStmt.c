#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int indisvalid; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_10__ {int /*<<< orphan*/  idxname; int /*<<< orphan*/  relation; int /*<<< orphan*/  concurrent; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ IndexStmt ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  INDEX_DROP_CLEAR_VALID ; 
 int /*<<< orphan*/  IndexRelationId ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsCoordinator () ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetNamespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_openrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_set_state_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PostProcessIndexStmt(IndexStmt *indexStmt)
{
	Relation relation = NULL;
	Oid indexRelationId = InvalidOid;
	Relation indexRelation = NULL;
	Relation pg_index = NULL;
	HeapTuple indexTuple = NULL;
	Form_pg_index indexForm = NULL;

	/* we are only processing CONCURRENT index statements */
	if (!indexStmt->concurrent)
	{
		return;
	}

	/* this logic only applies to the coordinator */
	if (!IsCoordinator())
	{
		return;
	}

	/* commit the current transaction and start anew */
	CommitTransactionCommand();
	StartTransactionCommand();

	/* get the affected relation and index */
	relation = heap_openrv(indexStmt->relation, ShareUpdateExclusiveLock);
	indexRelationId = get_relname_relid(indexStmt->idxname,
										RelationGetNamespace(relation));
	indexRelation = index_open(indexRelationId, RowExclusiveLock);

	/* close relations but retain locks */
	heap_close(relation, NoLock);
	index_close(indexRelation, NoLock);

	/* mark index as invalid, in-place (cannot be rolled back) */
	index_set_state_flags(indexRelationId, INDEX_DROP_CLEAR_VALID);

	/* re-open a transaction command from here on out */
	CommitTransactionCommand();
	StartTransactionCommand();

	/* now, update index's validity in a way that can roll back */
	pg_index = heap_open(IndexRelationId, RowExclusiveLock);

	indexTuple = SearchSysCacheCopy1(INDEXRELID, ObjectIdGetDatum(indexRelationId));
	Assert(HeapTupleIsValid(indexTuple)); /* better be present, we have lock! */

	/* mark as valid, save, and update pg_index indexes */
	indexForm = (Form_pg_index) GETSTRUCT(indexTuple);
	indexForm->indisvalid = true;

	CatalogTupleUpdate(pg_index, &indexTuple->t_self, indexTuple);

	/* clean up; index now marked valid, but ROLLBACK will mark invalid */
	heap_freetuple(indexTuple);
	heap_close(pg_index, RowExclusiveLock);
}