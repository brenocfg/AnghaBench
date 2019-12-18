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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ msDelay; scalar_t__ Para2; scalar_t__ Para1; int /*<<< orphan*/  CmdID; } ;
typedef  int /*<<< orphan*/  SwChnlCmdID ;
typedef  TYPE_1__ SwChnlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static u8 rtl8192_phy_SetSwChnlCmdArray(
	SwChnlCmd*		CmdTable,
	u32			CmdTableIdx,
	u32			CmdTableSz,
	SwChnlCmdID		CmdID,
	u32			Para1,
	u32			Para2,
	u32			msDelay
	)
{
	SwChnlCmd* pCmd;

	if(CmdTable == NULL)
	{
		RT_TRACE(COMP_ERR, "phy_SetSwChnlCmdArray(): CmdTable cannot be NULL.\n");
		return false;
	}
	if(CmdTableIdx >= CmdTableSz)
	{
		RT_TRACE(COMP_ERR, "phy_SetSwChnlCmdArray(): Access invalid index, please check size of the table, CmdTableIdx:%d, CmdTableSz:%d\n",
				CmdTableIdx, CmdTableSz);
		return false;
	}

	pCmd = CmdTable + CmdTableIdx;
	pCmd->CmdID = CmdID;
	pCmd->Para1 = Para1;
	pCmd->Para2 = Para2;
	pCmd->msDelay = msDelay;

	return true;
}