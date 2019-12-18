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

/* Variables and functions */
 scalar_t__ COMMIT_PROTOCOL_BARE ; 
 scalar_t__ MultiShardCommitProtocol ; 
 scalar_t__ SavedMultiShardCommitProtocol ; 

__attribute__((used)) static void
ResetShardPlacementTransactionState(void)
{
	if (MultiShardCommitProtocol == COMMIT_PROTOCOL_BARE)
	{
		MultiShardCommitProtocol = SavedMultiShardCommitProtocol;
		SavedMultiShardCommitProtocol = COMMIT_PROTOCOL_BARE;
	}
}