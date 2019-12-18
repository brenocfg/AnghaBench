#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  size_t u8 ;
struct scsi_device {int id; int lun; struct dc390_dcb* hostdata; TYPE_1__* host; } ;
struct dc390_dcb {int TargetID; int TargetLUN; int DevMode; int SyncMode; int SyncOffset; int NegoPeriod; int CtrlR4; int /*<<< orphan*/  CtrlR1; int /*<<< orphan*/  CtrlR3; int /*<<< orphan*/  SyncPeriod; struct dc390_acb* pDCBACB; struct dc390_dcb* pNextDCB; } ;
struct dc390_acb {size_t AdapterIndex; int glitch_cfg; int scan_devices; TYPE_2__* pScsiHost; struct dc390_dcb* pLastDCB; struct dc390_dcb* pLinkDCB; struct dc390_dcb* pDCBRunRobin; int /*<<< orphan*/  DCBCnt; } ;
struct TYPE_6__ {int EE_MODE1; size_t EE_SPEED; } ;
struct TYPE_5__ {int /*<<< orphan*/  this_id; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;
typedef  TYPE_3__* PEEprom ;

/* Variables and functions */
 int ACTIVE_NEGATION ; 
 int CTRL4_RESERVED ; 
 size_t EE_MODE2 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FAST_CLK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NEGATE_REQACK ; 
 int NEGATE_REQACKDATA ; 
 int PARITY_CHK_ ; 
 int /*<<< orphan*/  PARITY_ERR_REPO ; 
 int SYNC_ENABLE ; 
 int SYNC_NEGO_ ; 
 int SYNC_NEGO_DONE ; 
 int* dc390_clock_period1 ; 
 int** dc390_eepromBuf ; 
 struct dc390_dcb* dc390_findDCB (struct dc390_acb*,int,int /*<<< orphan*/ ) ; 
 struct dc390_dcb* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dc390_slave_alloc(struct scsi_device *scsi_device)
{
	struct dc390_acb *pACB = (struct dc390_acb*) scsi_device->host->hostdata;
	struct dc390_dcb *pDCB, *pDCB2 = NULL;
	uint id = scsi_device->id;
	uint lun = scsi_device->lun;

	pDCB = kzalloc(sizeof(struct dc390_dcb), GFP_KERNEL);
	if (!pDCB)
		return -ENOMEM;

	if (!pACB->DCBCnt++) {
		pACB->pLinkDCB = pDCB;
		pACB->pDCBRunRobin = pDCB;
	} else {
		pACB->pLastDCB->pNextDCB = pDCB;
	}
   
	pDCB->pNextDCB = pACB->pLinkDCB;
	pACB->pLastDCB = pDCB;

	pDCB->pDCBACB = pACB;
	pDCB->TargetID = id;
	pDCB->TargetLUN = lun;

	/*
	 * Some values are for all LUNs: Copy them 
	 * In a clean way: We would have an own structure for a SCSI-ID 
	 */
	if (lun && (pDCB2 = dc390_findDCB(pACB, id, 0))) {
		pDCB->DevMode = pDCB2->DevMode;
		pDCB->SyncMode = pDCB2->SyncMode & SYNC_NEGO_DONE;
		pDCB->SyncPeriod = pDCB2->SyncPeriod;
		pDCB->SyncOffset = pDCB2->SyncOffset;
		pDCB->NegoPeriod = pDCB2->NegoPeriod;
      
		pDCB->CtrlR3 = pDCB2->CtrlR3;
		pDCB->CtrlR4 = pDCB2->CtrlR4;
	} else {
		u8 index = pACB->AdapterIndex;
		PEEprom prom = (PEEprom) &dc390_eepromBuf[index][id << 2];

		pDCB->DevMode = prom->EE_MODE1;
		pDCB->NegoPeriod =
			(dc390_clock_period1[prom->EE_SPEED] * 25) >> 2;
		pDCB->CtrlR3 = FAST_CLK;
		pDCB->CtrlR4 = pACB->glitch_cfg | CTRL4_RESERVED;
		if (dc390_eepromBuf[index][EE_MODE2] & ACTIVE_NEGATION)
			pDCB->CtrlR4 |= NEGATE_REQACKDATA | NEGATE_REQACK;
	}

	if (pDCB->DevMode & SYNC_NEGO_)
		pDCB->SyncMode |= SYNC_ENABLE;
	else {
		pDCB->SyncMode = 0;
		pDCB->SyncOffset &= ~0x0f;
	}

	pDCB->CtrlR1 = pACB->pScsiHost->this_id;
	if (pDCB->DevMode & PARITY_CHK_)
		pDCB->CtrlR1 |= PARITY_ERR_REPO;

	pACB->scan_devices = 1;
	scsi_device->hostdata = pDCB;
	return 0;
}