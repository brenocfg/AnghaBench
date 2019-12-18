#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ connectionStateHash; scalar_t__ shardStateHash; struct TYPE_3__* columnCoercionPaths; struct TYPE_3__* columnOutputFunctions; struct TYPE_3__* copyOutState; } ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_1__ CitusCopyDestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  hash_destroy (scalar_t__) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
CitusCopyDestReceiverDestroy(DestReceiver *destReceiver)
{
	CitusCopyDestReceiver *copyDest = (CitusCopyDestReceiver *) destReceiver;

	if (copyDest->copyOutState)
	{
		pfree(copyDest->copyOutState);
	}

	if (copyDest->columnOutputFunctions)
	{
		pfree(copyDest->columnOutputFunctions);
	}

	if (copyDest->columnCoercionPaths)
	{
		pfree(copyDest->columnCoercionPaths);
	}

	if (copyDest->shardStateHash)
	{
		hash_destroy(copyDest->shardStateHash);
	}

	if (copyDest->connectionStateHash)
	{
		hash_destroy(copyDest->connectionStateHash);
	}

	pfree(copyDest);
}