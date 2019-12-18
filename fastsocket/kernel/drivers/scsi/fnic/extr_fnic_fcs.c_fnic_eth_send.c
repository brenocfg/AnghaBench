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
struct vnic_wq {int dummy; } ;
struct vlan_ethhdr {void* h_vlan_TCI; int /*<<< orphan*/  h_vlan_encapsulated_proto; void* h_vlan_proto; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct fnic {int /*<<< orphan*/ * wq_lock; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  pdev; int /*<<< orphan*/  vlan_hw_insert; struct vnic_wq* wq; } ;
struct fcoe_ctlr {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct fnic* fnic_from_ctlr (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fnic_queue_wq_eth_desc (struct vnic_wq*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct vlan_ethhdr*,struct ethhdr*,int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vnic_wq_desc_avail (struct vnic_wq*) ; 

void fnic_eth_send(struct fcoe_ctlr *fip, struct sk_buff *skb)
{
	struct fnic *fnic = fnic_from_ctlr(fip);
	struct vnic_wq *wq = &fnic->wq[0];
	dma_addr_t pa;
	struct ethhdr *eth_hdr;
	struct vlan_ethhdr *vlan_hdr;
	unsigned long flags;

	if (!fnic->vlan_hw_insert) {
		eth_hdr = (struct ethhdr *)skb_mac_header(skb);
		vlan_hdr = (struct vlan_ethhdr *)skb_push(skb,
				sizeof(*vlan_hdr) - sizeof(*eth_hdr));
		memcpy(vlan_hdr, eth_hdr, 2 * ETH_ALEN);
		vlan_hdr->h_vlan_proto = htons(ETH_P_8021Q);
		vlan_hdr->h_vlan_encapsulated_proto = eth_hdr->h_proto;
		vlan_hdr->h_vlan_TCI = htons(fnic->vlan_id);
	}

	pa = pci_map_single(fnic->pdev, skb->data, skb->len, PCI_DMA_TODEVICE);

	spin_lock_irqsave(&fnic->wq_lock[0], flags);
	if (!vnic_wq_desc_avail(wq)) {
		pci_unmap_single(fnic->pdev, pa, skb->len, PCI_DMA_TODEVICE);
		spin_unlock_irqrestore(&fnic->wq_lock[0], flags);
		kfree_skb(skb);
		return;
	}

	fnic_queue_wq_eth_desc(wq, skb, pa, skb->len,
			       0 /* hw inserts cos value */,
			       fnic->vlan_id, 1);
	spin_unlock_irqrestore(&fnic->wq_lock[0], flags);
}