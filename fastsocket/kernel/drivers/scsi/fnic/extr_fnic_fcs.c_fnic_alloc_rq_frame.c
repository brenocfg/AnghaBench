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
typedef  scalar_t__ u16 ;
struct vnic_rq {int /*<<< orphan*/  vdev; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct fnic {int /*<<< orphan*/  pdev; TYPE_1__* lport; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FC_FRAME_HEADROOM ; 
 scalar_t__ FC_FRAME_TAILROOM ; 
 scalar_t__ FC_MAX_FRAME ; 
 int /*<<< orphan*/  FNIC_FCS_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  fnic_queue_rq_desc (struct vnic_rq*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct fnic* vnic_dev_priv (int /*<<< orphan*/ ) ; 

int fnic_alloc_rq_frame(struct vnic_rq *rq)
{
	struct fnic *fnic = vnic_dev_priv(rq->vdev);
	struct sk_buff *skb;
	u16 len;
	dma_addr_t pa;

	len = FC_FRAME_HEADROOM + FC_MAX_FRAME + FC_FRAME_TAILROOM;
	skb = dev_alloc_skb(len);
	if (!skb) {
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
			     "Unable to allocate RQ sk_buff\n");
		return -ENOMEM;
	}
	skb_reset_mac_header(skb);
	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);
	skb_put(skb, len);
	pa = pci_map_single(fnic->pdev, skb->data, len, PCI_DMA_FROMDEVICE);
	fnic_queue_rq_desc(rq, skb, pa, len);
	return 0;
}