#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; } ;
struct ql_rcv_buf_cb {struct sk_buff* skb; } ;
struct ql3_adapter {scalar_t__ device_id; TYPE_2__* ndev; int /*<<< orphan*/  pdev; } ;
struct ib_mac_iocb_rsp {int /*<<< orphan*/  length; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ QL3022_DEVICE_ID ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_addr (struct ql_rcv_buf_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_len (struct ql_rcv_buf_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 struct ql_rcv_buf_cb* ql_get_lbuf (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_get_sbuf (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_release_to_lrg_buf_free_list (struct ql3_adapter*,struct ql_rcv_buf_cb*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void ql_process_mac_rx_intr(struct ql3_adapter *qdev,
				   struct ib_mac_iocb_rsp *ib_mac_rsp_ptr)
{
	struct ql_rcv_buf_cb *lrg_buf_cb1 = NULL;
	struct ql_rcv_buf_cb *lrg_buf_cb2 = NULL;
	struct sk_buff *skb;
	u16 length = le16_to_cpu(ib_mac_rsp_ptr->length);

	/*
	 * Get the inbound address list (small buffer).
	 */
	ql_get_sbuf(qdev);

	if (qdev->device_id == QL3022_DEVICE_ID)
		lrg_buf_cb1 = ql_get_lbuf(qdev);

	/* start of second buffer */
	lrg_buf_cb2 = ql_get_lbuf(qdev);
	skb = lrg_buf_cb2->skb;

	qdev->ndev->stats.rx_packets++;
	qdev->ndev->stats.rx_bytes += length;

	skb_put(skb, length);
	pci_unmap_single(qdev->pdev,
			 pci_unmap_addr(lrg_buf_cb2, mapaddr),
			 pci_unmap_len(lrg_buf_cb2, maplen),
			 PCI_DMA_FROMDEVICE);
	prefetch(skb->data);
	skb->ip_summed = CHECKSUM_NONE;
	skb->protocol = eth_type_trans(skb, qdev->ndev);

	netif_receive_skb(skb);
	lrg_buf_cb2->skb = NULL;

	if (qdev->device_id == QL3022_DEVICE_ID)
		ql_release_to_lrg_buf_free_list(qdev, lrg_buf_cb1);
	ql_release_to_lrg_buf_free_list(qdev, lrg_buf_cb2);
}