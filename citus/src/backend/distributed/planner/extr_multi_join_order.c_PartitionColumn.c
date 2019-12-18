#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32 ;
struct TYPE_4__ {void* varnoold; void* varno; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 TYPE_1__* DistPartitionKey (int /*<<< orphan*/ ) ; 

Var *
PartitionColumn(Oid relationId, uint32 rangeTableId)
{
	Var *partitionKey = DistPartitionKey(relationId);
	Var *partitionColumn = NULL;

	/* short circuit for reference tables */
	if (partitionKey == NULL)
	{
		return partitionColumn;
	}

	partitionColumn = partitionKey;
	partitionColumn->varno = rangeTableId;
	partitionColumn->varnoold = rangeTableId;

	return partitionColumn;
}