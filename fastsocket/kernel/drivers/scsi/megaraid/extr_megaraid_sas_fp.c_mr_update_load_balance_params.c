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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct MR_LD_RAID {int level; int rowSize; int spanDepth; scalar_t__ ldState; } ;
struct MR_FW_RAID_MAP_ALL {int dummy; } ;
struct LD_LOAD_BALANCE_INFO {int loadBalanceFlag; void** raid1DevHandle; } ;

/* Variables and functions */
 int MAX_LOGICAL_DRIVES ; 
 int /*<<< orphan*/  MR_ArPdGet (int /*<<< orphan*/ ,int,struct MR_FW_RAID_MAP_ALL*) ; 
 scalar_t__ MR_LD_STATE_OPTIMAL ; 
 struct MR_LD_RAID* MR_LdRaidGet (int,struct MR_FW_RAID_MAP_ALL*) ; 
 int /*<<< orphan*/  MR_LdSpanArrayGet (int,int /*<<< orphan*/ ,struct MR_FW_RAID_MAP_ALL*) ; 
 void* MR_PdDevHandleGet (int /*<<< orphan*/ ,struct MR_FW_RAID_MAP_ALL*) ; 
 int MR_TargetIdToLdGet (int,struct MR_FW_RAID_MAP_ALL*) ; 

void
mr_update_load_balance_params(struct MR_FW_RAID_MAP_ALL *map,
			      struct LD_LOAD_BALANCE_INFO *lbInfo)
{
	int ldCount;
	u16 ld;
	struct MR_LD_RAID *raid;

	for (ldCount = 0; ldCount < MAX_LOGICAL_DRIVES; ldCount++) {
		ld = MR_TargetIdToLdGet(ldCount, map);
		if (ld >= MAX_LOGICAL_DRIVES) {
			lbInfo[ldCount].loadBalanceFlag = 0;
			continue;
		}

		raid = MR_LdRaidGet(ld, map);

		/* Two drive Optimal RAID 1 */
		if ((raid->level == 1)  &&  (raid->rowSize == 2) &&
		    (raid->spanDepth == 1) && raid->ldState ==
		    MR_LD_STATE_OPTIMAL) {
			u32 pd, arRef;

			lbInfo[ldCount].loadBalanceFlag = 1;

			/* Get the array on which this span is present */
			arRef = MR_LdSpanArrayGet(ld, 0, map);

			/* Get the Pd */
			pd = MR_ArPdGet(arRef, 0, map);
			/* Get dev handle from Pd */
			lbInfo[ldCount].raid1DevHandle[0] =
				MR_PdDevHandleGet(pd, map);
			/* Get the Pd */
			pd = MR_ArPdGet(arRef, 1, map);

			/* Get the dev handle from Pd */
			lbInfo[ldCount].raid1DevHandle[1] =
				MR_PdDevHandleGet(pd, map);
		} else
			lbInfo[ldCount].loadBalanceFlag = 0;
	}
}