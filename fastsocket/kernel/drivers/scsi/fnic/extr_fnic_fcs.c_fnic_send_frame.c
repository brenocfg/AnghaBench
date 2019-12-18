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
typedef  int u32 ;
struct vnic_wq {int dummy; } ;
struct vlan_ethhdr {void* h_vlan_TCI; void* h_vlan_encapsulated_proto; void* h_vlan_proto; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dest_addr; scalar_t__ map_dest; } ;
struct fnic {int /*<<< orphan*/ * wq_lock; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  pdev; int /*<<< orphan*/  data_src_addr; TYPE_1__ ctlr; int /*<<< orphan*/  vlan_hw_insert; int /*<<< orphan*/  lport; struct vnic_wq* wq; } ;
struct fcoe_hdr {int /*<<< orphan*/  fcoe_sof; } ;
struct fc_frame_header {scalar_t__ fh_r_ctl; int /*<<< orphan*/  fh_d_id; } ;
struct fc_frame {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; void* h_proto; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_FCOE ; 
 int /*<<< orphan*/  FC_FCOE_ENCAPS_VER (struct fcoe_hdr*,scalar_t__) ; 
 scalar_t__ FC_FCOE_VER ; 
 scalar_t__ FC_RCTL_ELS_REQ ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  fc_fcoe_set_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 scalar_t__ fcoe_ctlr_els_send (TYPE_1__*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  fnic_queue_wq_desc (struct vnic_wq*,struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct sk_buff* fp_skb (struct fc_frame*) ; 
 int /*<<< orphan*/  fr_eof (struct fc_frame*) ; 
 int /*<<< orphan*/  fr_sof (struct fc_frame*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fcoe_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,struct ethhdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vnic_wq_desc_avail (struct vnic_wq*) ; 

__attribute__((used)) static int fnic_send_frame(struct fnic *fnic, struct fc_frame *fp)
{
	struct vnic_wq *wq = &fnic->wq[0];
	struct sk_buff *skb;
	dma_addr_t pa;
	struct ethhdr *eth_hdr;
	struct vlan_ethhdr *vlan_hdr;
	struct fcoe_hdr *fcoe_hdr;
	struct fc_frame_header *fh;
	u32 tot_len, eth_hdr_len;
	int ret = 0;
	unsigned long flags;

	fh = fc_frame_header_get(fp);
	skb = fp_skb(fp);

	if (unlikely(fh->fh_r_ctl == FC_RCTL_ELS_REQ) &&
	    fcoe_ctlr_els_send(&fnic->ctlr, fnic->lport, skb))
		return 0;

	if (!fnic->vlan_hw_insert) {
		eth_hdr_len = sizeof(*vlan_hdr) + sizeof(*fcoe_hdr);
		vlan_hdr = (struct vlan_ethhdr *)skb_push(skb, eth_hdr_len);
		eth_hdr = (struct ethhdr *)vlan_hdr;
		vlan_hdr->h_vlan_proto = htons(ETH_P_8021Q);
		vlan_hdr->h_vlan_encapsulated_proto = htons(ETH_P_FCOE);
		vlan_hdr->h_vlan_TCI = htons(fnic->vlan_id);
		fcoe_hdr = (struct fcoe_hdr *)(vlan_hdr + 1);
	} else {
		eth_hdr_len = sizeof(*eth_hdr) + sizeof(*fcoe_hdr);
		eth_hdr = (struct ethhdr *)skb_push(skb, eth_hdr_len);
		eth_hdr->h_proto = htons(ETH_P_FCOE);
		fcoe_hdr = (struct fcoe_hdr *)(eth_hdr + 1);
	}

	if (fnic->ctlr.map_dest)
		fc_fcoe_set_mac(eth_hdr->h_dest, fh->fh_d_id);
	else
		memcpy(eth_hdr->h_dest, fnic->ctlr.dest_addr, ETH_ALEN);
	memcpy(eth_hdr->h_source, fnic->data_src_addr, ETH_ALEN);

	tot_len = skb->len;
	BUG_ON(tot_len % 4);

	memset(fcoe_hdr, 0, sizeof(*fcoe_hdr));
	fcoe_hdr->fcoe_sof = fr_sof(fp);
	if (FC_FCOE_VER)
		FC_FCOE_ENCAPS_VER(fcoe_hdr, FC_FCOE_VER);

	pa = pci_map_single(fnic->pdev, eth_hdr, tot_len, PCI_DMA_TODEVICE);

	spin_lock_irqsave(&fnic->wq_lock[0], flags);

	if (!vnic_wq_desc_avail(wq)) {
		pci_unmap_single(fnic->pdev, pa,
				 tot_len, PCI_DMA_TODEVICE);
		ret = -1;
		goto fnic_send_frame_end;
	}

	fnic_queue_wq_desc(wq, skb, pa, tot_len, fr_eof(fp),
			   0 /* hw inserts cos value */,
			   fnic->vlan_id, 1, 1, 1);
fnic_send_frame_end:
	spin_unlock_irqrestore(&fnic->wq_lock[0], flags);

	if (ret)
		dev_kfree_skb_any(fp_skb(fp));

	return ret;
}