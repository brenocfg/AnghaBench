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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * DeferErrorIfPartitionTableNotSingleReplicated (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RaiseDeferredError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
EnsurePartitionTableNotReplicated(Oid relationId)
{
	DeferredErrorMessage *deferredError =
		DeferErrorIfPartitionTableNotSingleReplicated(relationId);
	if (deferredError != NULL)
	{
		RaiseDeferredError(deferredError, ERROR);
	}
}