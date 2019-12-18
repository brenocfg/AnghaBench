#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_2__ {int /*<<< orphan*/  colocationid; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_dist_colocation ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_colocation_distributioncolumntype ; 
 int /*<<< orphan*/  Anum_pg_dist_colocation_replicationfactor ; 
 int /*<<< orphan*/  Anum_pg_dist_colocation_shardcount ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DistColocationConfigurationIndexId () ; 
 int /*<<< orphan*/  DistColocationRelationId () ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INVALID_COLOCATION_ID ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UInt32GetDatum (int) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ ) ; 

uint32
ColocationId(int shardCount, int replicationFactor, Oid distributionColumnType)
{
	uint32 colocationId = INVALID_COLOCATION_ID;
	HeapTuple colocationTuple = NULL;
	SysScanDesc scanDescriptor;
	const int scanKeyCount = 3;
	ScanKeyData scanKey[3];
	bool indexOK = true;

	Relation pgDistColocation = heap_open(DistColocationRelationId(), AccessShareLock);

	/* set scan arguments */
	ScanKeyInit(&scanKey[0], Anum_pg_dist_colocation_shardcount,
				BTEqualStrategyNumber, F_INT4EQ, UInt32GetDatum(shardCount));
	ScanKeyInit(&scanKey[1], Anum_pg_dist_colocation_replicationfactor,
				BTEqualStrategyNumber, F_INT4EQ, Int32GetDatum(replicationFactor));
	ScanKeyInit(&scanKey[2], Anum_pg_dist_colocation_distributioncolumntype,
				BTEqualStrategyNumber, F_OIDEQ, ObjectIdGetDatum(distributionColumnType));

	scanDescriptor = systable_beginscan(pgDistColocation,
										DistColocationConfigurationIndexId(),
										indexOK, NULL, scanKeyCount, scanKey);

	colocationTuple = systable_getnext(scanDescriptor);
	if (HeapTupleIsValid(colocationTuple))
	{
		Form_pg_dist_colocation colocationForm =
			(Form_pg_dist_colocation) GETSTRUCT(colocationTuple);

		colocationId = colocationForm->colocationid;
	}

	systable_endscan(scanDescriptor);
	heap_close(pgDistColocation, AccessShareLock);

	return colocationId;
}