#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_11__ {int binary; } ;
struct TYPE_10__ {TYPE_2__* shardState; TYPE_1__* connectionState; } ;
struct TYPE_9__ {int /*<<< orphan*/  shardId; } ;
struct TYPE_8__ {int /*<<< orphan*/ * connection; } ;
typedef  int /*<<< orphan*/  MultiConnection ;
typedef  TYPE_3__ CopyPlacementState ;
typedef  TYPE_4__* CopyOutState ;

/* Variables and functions */
 int /*<<< orphan*/  EndRemoteCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendCopyBinaryFooters (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
EndPlacementStateCopyCommand(CopyPlacementState *placementState,
							 CopyOutState copyOutState)
{
	MultiConnection *connection = placementState->connectionState->connection;
	uint64 shardId = placementState->shardState->shardId;
	bool binaryCopy = copyOutState->binary;

	/* send footers and end copy command */
	if (binaryCopy)
	{
		SendCopyBinaryFooters(copyOutState, shardId, list_make1(connection));
	}

	EndRemoteCopy(shardId, list_make1(connection));
}