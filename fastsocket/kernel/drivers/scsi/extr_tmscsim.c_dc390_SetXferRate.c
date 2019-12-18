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
typedef  scalar_t__ u8 ;
struct dc390_dcb {scalar_t__ TargetID; struct dc390_dcb* pNextDCB; int /*<<< orphan*/  SyncMode; int /*<<< orphan*/  CtrlR4; int /*<<< orphan*/  CtrlR3; int /*<<< orphan*/  SyncOffset; int /*<<< orphan*/  SyncPeriod; int /*<<< orphan*/  TargetLUN; } ;
struct dc390_acb {scalar_t__ DCBCnt; struct dc390_dcb* pLinkDCB; int /*<<< orphan*/  scan_devices; } ;

/* Variables and functions */

__attribute__((used)) static void
dc390_SetXferRate( struct dc390_acb* pACB, struct dc390_dcb* pDCB )
{
    u8  bval, i, cnt;
    struct dc390_dcb*   ptr;

    if( !(pDCB->TargetLUN) )
    {
	if( !pACB->scan_devices )
	{
	    ptr = pACB->pLinkDCB;
	    cnt = pACB->DCBCnt;
	    bval = pDCB->TargetID;
	    for(i=0; i<cnt; i++)
	    {
		if( ptr->TargetID == bval )
		{
		    ptr->SyncPeriod = pDCB->SyncPeriod;
		    ptr->SyncOffset = pDCB->SyncOffset;
		    ptr->CtrlR3 = pDCB->CtrlR3;
		    ptr->CtrlR4 = pDCB->CtrlR4;
		    ptr->SyncMode = pDCB->SyncMode;
		}
		ptr = ptr->pNextDCB;
	    }
	}
    }
    return;
}