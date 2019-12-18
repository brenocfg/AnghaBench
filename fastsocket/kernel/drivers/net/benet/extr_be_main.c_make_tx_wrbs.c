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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct skb_frag_struct {int dummy; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data_len; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
struct be_queue_info {int /*<<< orphan*/  head; } ;
struct be_eth_wrb {scalar_t__ frag_len; } ;
struct be_eth_hdr_wrb {scalar_t__ frag_len; } ;
struct be_adapter {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int nr_frags; struct skb_frag_struct* frags; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  be_dws_cpu_to_le (struct be_eth_wrb*,int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_head_inc (struct be_queue_info*) ; 
 struct be_eth_wrb* queue_head_node (struct be_queue_info*) ; 
 int /*<<< orphan*/  skb_frag_dma_map (struct device*,struct skb_frag_struct const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (struct skb_frag_struct const*) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  unmap_tx_frag (struct device*,struct be_eth_wrb*,int) ; 
 int /*<<< orphan*/  wrb_fill (struct be_eth_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrb_fill_hdr (struct be_adapter*,struct be_eth_wrb*,struct sk_buff*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int make_tx_wrbs(struct be_adapter *adapter, struct be_queue_info *txq,
		struct sk_buff *skb, u32 wrb_cnt, bool dummy_wrb,
		bool skip_hw_vlan)
{
	dma_addr_t busaddr;
	int i, copied = 0;
	struct device *dev = &adapter->pdev->dev;
	struct sk_buff *first_skb = skb;
	struct be_eth_wrb *wrb;
	struct be_eth_hdr_wrb *hdr;
	bool map_single = false;
	u16 map_head;

	hdr = queue_head_node(txq);
	queue_head_inc(txq);
	map_head = txq->head;

	if (skb->len > skb->data_len) {
		int len = skb_headlen(skb);
		busaddr = dma_map_single(dev, skb->data, len, DMA_TO_DEVICE);
		if (dma_mapping_error(dev, busaddr))
			goto dma_err;
		map_single = true;
		wrb = queue_head_node(txq);
		wrb_fill(wrb, busaddr, len);
		be_dws_cpu_to_le(wrb, sizeof(*wrb));
		queue_head_inc(txq);
		copied += len;
	}

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		const struct skb_frag_struct *frag =
			&skb_shinfo(skb)->frags[i];
		busaddr = skb_frag_dma_map(dev, frag, 0,
					   skb_frag_size(frag), DMA_TO_DEVICE);
		if (dma_mapping_error(dev, busaddr))
			goto dma_err;
		wrb = queue_head_node(txq);
		wrb_fill(wrb, busaddr, skb_frag_size(frag));
		be_dws_cpu_to_le(wrb, sizeof(*wrb));
		queue_head_inc(txq);
		copied += skb_frag_size(frag);
	}

	if (dummy_wrb) {
		wrb = queue_head_node(txq);
		wrb_fill(wrb, 0, 0);
		be_dws_cpu_to_le(wrb, sizeof(*wrb));
		queue_head_inc(txq);
	}

	wrb_fill_hdr(adapter, hdr, first_skb, wrb_cnt, copied, skip_hw_vlan);
	be_dws_cpu_to_le(hdr, sizeof(*hdr));

	return copied;
dma_err:
	txq->head = map_head;
	while (copied) {
		wrb = queue_head_node(txq);
		unmap_tx_frag(dev, wrb, map_single);
		map_single = false;
		copied -= wrb->frag_len;
		queue_head_inc(txq);
	}
	return 0;
}