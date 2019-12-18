#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  skb; int /*<<< orphan*/  skb_dma; } ;
struct TYPE_6__ {int nRxDescs1; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  pcid; TYPE_2__* aRD1Ring; TYPE_1__ sOpts; } ;
struct TYPE_7__ {TYPE_4__* pRDInfo; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PSRxDesc ;
typedef  TYPE_3__* PSDevice ;
typedef  TYPE_4__* PDEVICE_RD_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_free_rd1_ring(PSDevice pDevice) {
    int i;


    for (i = 0; i < pDevice->sOpts.nRxDescs1; i++) {
        PSRxDesc        pDesc=&(pDevice->aRD1Ring[i]);
        PDEVICE_RD_INFO  pRDInfo=pDesc->pRDInfo;

        pci_unmap_single(pDevice->pcid,pRDInfo->skb_dma,
           pDevice->rx_buf_sz, PCI_DMA_FROMDEVICE);

        dev_kfree_skb(pRDInfo->skb);

        kfree((PVOID)pDesc->pRDInfo);
    }

}