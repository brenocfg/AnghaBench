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
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_5__ {scalar_t__ OS_Cookie; } ;
struct TYPE_4__ {void* pSrcBufData; size_t SrcBufLen; } ;
typedef  TYPE_1__* PTX_BLK ;
typedef  TYPE_2__* PRTMP_ADAPTER ;
typedef  TYPE_3__* POS_COOKIE ;

/* Variables and functions */
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,void*,size_t,int) ; 

dma_addr_t linux_pci_map_single(void *handle, void *ptr, size_t size, int sd_idx, int direction)
{
	PRTMP_ADAPTER pAd;
	POS_COOKIE pObj;

	/*
		------ Porting Information ------
		> For Tx Alloc:
			mgmt packets => sd_idx = 0
			SwIdx: pAd->MgmtRing.TxCpuIdx
			pTxD : pAd->MgmtRing.Cell[SwIdx].AllocVa;

			data packets => sd_idx = 1
	 		TxIdx : pAd->TxRing[pTxBlk->QueIdx].TxCpuIdx
	 		QueIdx: pTxBlk->QueIdx
	 		pTxD  : pAd->TxRing[pTxBlk->QueIdx].Cell[TxIdx].AllocVa;

	 	> For Rx Alloc:
	 		sd_idx = -1
	*/

	pAd = (PRTMP_ADAPTER)handle;
	pObj = (POS_COOKIE)pAd->OS_Cookie;

	if (sd_idx == 1)
	{
		PTX_BLK		pTxBlk;
		pTxBlk = (PTX_BLK)ptr;
		return pci_map_single(pObj->pci_dev, pTxBlk->pSrcBufData, pTxBlk->SrcBufLen, direction);
	}
	else
	{
		return pci_map_single(pObj->pci_dev, ptr, size, direction);
	}

}