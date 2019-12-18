#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* rd_partdesc; } ;
struct TYPE_5__ {int nparts; int /*<<< orphan*/ * oids; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  PartitionedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

List *
PartitionList(Oid parentRelationId)
{
	Relation rel = heap_open(parentRelationId, AccessShareLock);
	List *partitionList = NIL;

	int partitionIndex = 0;
	int partitionCount = 0;

	if (!PartitionedTable(parentRelationId))
	{
		char *relationName = get_rel_name(parentRelationId);

		ereport(ERROR, (errmsg("\"%s\" is not a parent table", relationName)));
	}

	Assert(rel->rd_partdesc != NULL);

	partitionCount = rel->rd_partdesc->nparts;
	for (partitionIndex = 0; partitionIndex < partitionCount; ++partitionIndex)
	{
		partitionList =
			lappend_oid(partitionList, rel->rd_partdesc->oids[partitionIndex]);
	}

	/* keep the lock */
	heap_close(rel, NoLock);

	return partitionList;
}