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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct LD_LOAD_BALANCE_INFO {scalar_t__* last_accessed_block; int /*<<< orphan*/ * scsi_pending_cmds; } ;

/* Variables and functions */
 scalar_t__ ABS_DIFF (scalar_t__,scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

u8 megasas_get_best_arm(struct LD_LOAD_BALANCE_INFO *lbInfo, u8 arm, u64 block,
			u32 count)
{
	u16     pend0, pend1;
	u64     diff0, diff1;
	u8      bestArm;

	/* get the pending cmds for the data and mirror arms */
	pend0 = atomic_read(&lbInfo->scsi_pending_cmds[0]);
	pend1 = atomic_read(&lbInfo->scsi_pending_cmds[1]);

	/* Determine the disk whose head is nearer to the req. block */
	diff0 = ABS_DIFF(block, lbInfo->last_accessed_block[0]);
	diff1 = ABS_DIFF(block, lbInfo->last_accessed_block[1]);
	bestArm = (diff0 <= diff1 ? 0 : 1);

	/*Make balance count from 16 to 4 to keep driver in sync with Firmware*/
	if ((bestArm == arm && pend0 > pend1 + 4)  ||
	    (bestArm != arm && pend1 > pend0 + 4))
		bestArm ^= 1;

	/* Update the last accessed block on the correct pd */
	lbInfo->last_accessed_block[bestArm] = block + count - 1;

	return bestArm;
}