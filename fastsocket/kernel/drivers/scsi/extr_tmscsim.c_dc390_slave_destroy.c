#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {scalar_t__ hostdata; TYPE_1__* host; } ;
struct dc390_dcb {int GoingSRBCnt; struct dc390_dcb* pNextDCB; } ;
struct dc390_acb {int /*<<< orphan*/  DCBCnt; struct dc390_dcb* pDCBRunRobin; struct dc390_dcb* pLinkDCB; struct dc390_dcb* pActiveDCB; struct dc390_dcb* pLastDCB; scalar_t__ scan_devices; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct dc390_dcb*) ; 

__attribute__((used)) static void dc390_slave_destroy(struct scsi_device *scsi_device)
{
	struct dc390_acb* pACB = (struct dc390_acb*) scsi_device->host->hostdata;
	struct dc390_dcb* pDCB = (struct dc390_dcb*) scsi_device->hostdata;
	struct dc390_dcb* pPrevDCB = pACB->pLinkDCB;

	pACB->scan_devices = 0;

	BUG_ON(pDCB->GoingSRBCnt > 1);
	
	if (pDCB == pACB->pLinkDCB) {
		if (pACB->pLastDCB == pDCB) {
			pDCB->pNextDCB = NULL;
			pACB->pLastDCB = NULL;
		}
		pACB->pLinkDCB = pDCB->pNextDCB;
	} else {
		while (pPrevDCB->pNextDCB != pDCB)
			pPrevDCB = pPrevDCB->pNextDCB;
		pPrevDCB->pNextDCB = pDCB->pNextDCB;
		if (pDCB == pACB->pLastDCB)
			pACB->pLastDCB = pPrevDCB;
	}

	if (pDCB == pACB->pActiveDCB)
		pACB->pActiveDCB = NULL;
	if (pDCB == pACB->pLinkDCB)
		pACB->pLinkDCB = pDCB->pNextDCB;
	if (pDCB == pACB->pDCBRunRobin)
		pACB->pDCBRunRobin = pDCB->pNextDCB;
	kfree(pDCB); 
	
	pACB->DCBCnt--;
}