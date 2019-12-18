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
struct TYPE_4__ {int max_aggr; int /*<<< orphan*/  get_skb_header; int /*<<< orphan*/  lro_arr; scalar_t__ frag_align_pad; int /*<<< orphan*/  max_desc; void* ip_summed_aggr; void* ip_summed; int /*<<< orphan*/  features; int /*<<< orphan*/  stats; TYPE_2__* dev; } ;
struct rx_queue {int index; int rx_ring_size; int rx_desc_area_size; scalar_t__ rx_desc_dma; int /*<<< orphan*/ * rx_desc_area; int /*<<< orphan*/  lro_arr; TYPE_1__ lro_mgr; int /*<<< orphan*/ * rx_skb; scalar_t__ rx_used_desc; scalar_t__ rx_curr_desc; scalar_t__ rx_desc_count; } ;
struct rx_desc {scalar_t__ next_desc_ptr; } ;
struct mv643xx_eth_private {int rx_ring_size; int rx_desc_sram_size; TYPE_2__* dev; scalar_t__ rx_desc_sram_addr; struct rx_queue* rxq; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 void* CHECKSUM_UNNECESSARY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LRO_F_NAPI ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv643xx_get_skb_header ; 

__attribute__((used)) static int rxq_init(struct mv643xx_eth_private *mp, int index)
{
	struct rx_queue *rxq = mp->rxq + index;
	struct rx_desc *rx_desc;
	int size;
	int i;

	rxq->index = index;

	rxq->rx_ring_size = mp->rx_ring_size;

	rxq->rx_desc_count = 0;
	rxq->rx_curr_desc = 0;
	rxq->rx_used_desc = 0;

	size = rxq->rx_ring_size * sizeof(struct rx_desc);

	if (index == 0 && size <= mp->rx_desc_sram_size) {
		rxq->rx_desc_area = ioremap(mp->rx_desc_sram_addr,
						mp->rx_desc_sram_size);
		rxq->rx_desc_dma = mp->rx_desc_sram_addr;
	} else {
		rxq->rx_desc_area = dma_alloc_coherent(mp->dev->dev.parent,
						       size, &rxq->rx_desc_dma,
						       GFP_KERNEL);
	}

	if (rxq->rx_desc_area == NULL) {
		dev_printk(KERN_ERR, &mp->dev->dev,
			   "can't allocate rx ring (%d bytes)\n", size);
		goto out;
	}
	memset(rxq->rx_desc_area, 0, size);

	rxq->rx_desc_area_size = size;
	rxq->rx_skb = kmalloc(rxq->rx_ring_size * sizeof(*rxq->rx_skb),
								GFP_KERNEL);
	if (rxq->rx_skb == NULL) {
		dev_printk(KERN_ERR, &mp->dev->dev,
			   "can't allocate rx skb ring\n");
		goto out_free;
	}

	rx_desc = (struct rx_desc *)rxq->rx_desc_area;
	for (i = 0; i < rxq->rx_ring_size; i++) {
		int nexti;

		nexti = i + 1;
		if (nexti == rxq->rx_ring_size)
			nexti = 0;

		rx_desc[i].next_desc_ptr = rxq->rx_desc_dma +
					nexti * sizeof(struct rx_desc);
	}

	rxq->lro_mgr.dev = mp->dev;
	memset(&rxq->lro_mgr.stats, 0, sizeof(rxq->lro_mgr.stats));
	rxq->lro_mgr.features = LRO_F_NAPI;
	rxq->lro_mgr.ip_summed = CHECKSUM_UNNECESSARY;
	rxq->lro_mgr.ip_summed_aggr = CHECKSUM_UNNECESSARY;
	rxq->lro_mgr.max_desc = ARRAY_SIZE(rxq->lro_arr);
	rxq->lro_mgr.max_aggr = 32;
	rxq->lro_mgr.frag_align_pad = 0;
	rxq->lro_mgr.lro_arr = rxq->lro_arr;
	rxq->lro_mgr.get_skb_header = mv643xx_get_skb_header;

	memset(&rxq->lro_arr, 0, sizeof(rxq->lro_arr));

	return 0;


out_free:
	if (index == 0 && size <= mp->rx_desc_sram_size)
		iounmap(rxq->rx_desc_area);
	else
		dma_free_coherent(mp->dev->dev.parent, size,
				  rxq->rx_desc_area,
				  rxq->rx_desc_dma);

out:
	return -ENOMEM;
}