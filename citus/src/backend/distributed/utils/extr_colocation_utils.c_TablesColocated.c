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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ INVALID_COLOCATION_ID ; 
 scalar_t__ TableColocationId (scalar_t__) ; 

bool
TablesColocated(Oid leftDistributedTableId, Oid rightDistributedTableId)
{
	uint32 leftColocationId = INVALID_COLOCATION_ID;
	uint32 rightColocationId = INVALID_COLOCATION_ID;

	if (leftDistributedTableId == rightDistributedTableId)
	{
		return true;
	}

	leftColocationId = TableColocationId(leftDistributedTableId);
	rightColocationId = TableColocationId(rightDistributedTableId);
	if (leftColocationId == INVALID_COLOCATION_ID ||
		rightColocationId == INVALID_COLOCATION_ID)
	{
		return false;
	}

	return leftColocationId == rightColocationId;
}