#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  skb_dma; TYPE_6__* skb; } ;
struct TYPE_14__ {scalar_t__ rx_buf_sz; int /*<<< orphan*/  pcid; int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {void* wReqCount; } ;
struct TYPE_11__ {int /*<<< orphan*/  f1Owner; void* wResCount; } ;
struct TYPE_13__ {int /*<<< orphan*/  buff_addr; TYPE_2__ m_rd1RD1; TYPE_1__ m_rd0RD0; TYPE_5__* pRDInfo; } ;
typedef  TYPE_3__* PSRxDesc ;
typedef  TYPE_4__* PSDevice ;
typedef  TYPE_5__* PDEVICE_RD_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_6__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OWNED_BY_NIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  TRUE ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_6__* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tail_pointer (TYPE_6__*) ; 

__attribute__((used)) static BOOL device_alloc_rx_buf(PSDevice pDevice, PSRxDesc pRD) {

    PDEVICE_RD_INFO pRDInfo=pRD->pRDInfo;


    pRDInfo->skb = dev_alloc_skb((int)pDevice->rx_buf_sz);
#ifdef	PLICE_DEBUG
	//printk("device_alloc_rx_buf:skb is %x\n",pRDInfo->skb);
#endif
    if (pRDInfo->skb==NULL)
        return FALSE;
    ASSERT(pRDInfo->skb);
    pRDInfo->skb->dev = pDevice->dev;
    pRDInfo->skb_dma = pci_map_single(pDevice->pcid, skb_tail_pointer(pRDInfo->skb),
				      pDevice->rx_buf_sz, PCI_DMA_FROMDEVICE);
    *((unsigned int *) &(pRD->m_rd0RD0)) = 0; /* FIX cast */

    pRD->m_rd0RD0.wResCount = cpu_to_le16(pDevice->rx_buf_sz);
    pRD->m_rd0RD0.f1Owner = OWNED_BY_NIC;
    pRD->m_rd1RD1.wReqCount = cpu_to_le16(pDevice->rx_buf_sz);
    pRD->buff_addr = cpu_to_le32(pRDInfo->skb_dma);

    return TRUE;
}