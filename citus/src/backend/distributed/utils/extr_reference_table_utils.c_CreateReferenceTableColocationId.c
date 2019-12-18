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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ ColocationId (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateColocationGroup (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_COLOCATION_ID ; 
 int /*<<< orphan*/  InvalidOid ; 

uint32
CreateReferenceTableColocationId()
{
	uint32 colocationId = INVALID_COLOCATION_ID;
	int shardCount = 1;
	Oid distributionColumnType = InvalidOid;

	/*
	 * We don't maintain replication factor of reference tables anymore and
	 * just use -1 instead. We don't use this value in any places.
	 */
	int replicationFactor = -1;

	/* check for existing colocations */
	colocationId = ColocationId(shardCount, replicationFactor, distributionColumnType);
	if (colocationId == INVALID_COLOCATION_ID)
	{
		colocationId = CreateColocationGroup(shardCount, replicationFactor,
											 distributionColumnType);
	}

	return colocationId;
}