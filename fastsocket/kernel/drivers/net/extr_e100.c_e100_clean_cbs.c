#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ count; } ;
struct TYPE_7__ {TYPE_1__ cbs; } ;
struct nic {scalar_t__ cbs_avail; struct cb* cbs; struct cb* cb_to_clean; struct cb* cb_to_send; struct cb* cb_to_use; int /*<<< orphan*/  cuc_cmd; int /*<<< orphan*/  cbs_dma_addr; int /*<<< orphan*/  cbs_pool; int /*<<< orphan*/  pdev; TYPE_2__ params; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_9__ {TYPE_3__ tbd; } ;
struct TYPE_10__ {TYPE_4__ tcb; } ;
struct cb {struct cb* next; scalar_t__ skb; TYPE_5__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  cuc_start ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,struct cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e100_clean_cbs(struct nic *nic)
{
	if (nic->cbs) {
		while (nic->cbs_avail != nic->params.cbs.count) {
			struct cb *cb = nic->cb_to_clean;
			if (cb->skb) {
				pci_unmap_single(nic->pdev,
					le32_to_cpu(cb->u.tcb.tbd.buf_addr),
					le16_to_cpu(cb->u.tcb.tbd.size),
					PCI_DMA_TODEVICE);
				dev_kfree_skb(cb->skb);
			}
			nic->cb_to_clean = nic->cb_to_clean->next;
			nic->cbs_avail++;
		}
		pci_pool_free(nic->cbs_pool, nic->cbs, nic->cbs_dma_addr);
		nic->cbs = NULL;
		nic->cbs_avail = 0;
	}
	nic->cuc_cmd = cuc_start;
	nic->cb_to_use = nic->cb_to_send = nic->cb_to_clean =
		nic->cbs;
}