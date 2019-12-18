#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spider_net_hw_descr {int buf_size; int dmac_cmd_status; int /*<<< orphan*/  buf_addr; scalar_t__ data_error; scalar_t__ data_status; scalar_t__ valid_size; scalar_t__ result_size; } ;
struct spider_net_descr {TYPE_2__* skb; struct spider_net_hw_descr* hwdescr; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_iommu_map_error; int /*<<< orphan*/  alloc_rx_skb_error; } ;
struct spider_net_card {TYPE_1__ spider_stats; TYPE_4__* netdev; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int SPIDER_NET_DESCR_CARDOWNED ; 
 int SPIDER_NET_DESCR_NOT_IN_USE ; 
 int SPIDER_NET_DMAC_NOINTR_COMPLETE ; 
 int SPIDER_NET_MAX_FRAME ; 
 int SPIDER_NET_RXBUF_ALIGN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_2__*) ; 
 scalar_t__ net_ratelimit () ; 
 TYPE_2__* netdev_alloc_skb (TYPE_4__*,int) ; 
 scalar_t__ netif_msg_rx_err (struct spider_net_card*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_2__*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
spider_net_prepare_rx_descr(struct spider_net_card *card,
			    struct spider_net_descr *descr)
{
	struct spider_net_hw_descr *hwdescr = descr->hwdescr;
	dma_addr_t buf;
	int offset;
	int bufsize;

	/* we need to round up the buffer size to a multiple of 128 */
	bufsize = (SPIDER_NET_MAX_FRAME + SPIDER_NET_RXBUF_ALIGN - 1) &
		(~(SPIDER_NET_RXBUF_ALIGN - 1));

	/* and we need to have it 128 byte aligned, therefore we allocate a
	 * bit more */
	/* allocate an skb */
	descr->skb = netdev_alloc_skb(card->netdev,
				      bufsize + SPIDER_NET_RXBUF_ALIGN - 1);
	if (!descr->skb) {
		if (netif_msg_rx_err(card) && net_ratelimit())
			dev_err(&card->netdev->dev,
			        "Not enough memory to allocate rx buffer\n");
		card->spider_stats.alloc_rx_skb_error++;
		return -ENOMEM;
	}
	hwdescr->buf_size = bufsize;
	hwdescr->result_size = 0;
	hwdescr->valid_size = 0;
	hwdescr->data_status = 0;
	hwdescr->data_error = 0;

	offset = ((unsigned long)descr->skb->data) &
		(SPIDER_NET_RXBUF_ALIGN - 1);
	if (offset)
		skb_reserve(descr->skb, SPIDER_NET_RXBUF_ALIGN - offset);
	/* iommu-map the skb */
	buf = pci_map_single(card->pdev, descr->skb->data,
			SPIDER_NET_MAX_FRAME, PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(card->pdev, buf)) {
		dev_kfree_skb_any(descr->skb);
		descr->skb = NULL;
		if (netif_msg_rx_err(card) && net_ratelimit())
			dev_err(&card->netdev->dev, "Could not iommu-map rx buffer\n");
		card->spider_stats.rx_iommu_map_error++;
		hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_NOT_IN_USE;
	} else {
		hwdescr->buf_addr = buf;
		wmb();
		hwdescr->dmac_cmd_status = SPIDER_NET_DESCR_CARDOWNED |
					 SPIDER_NET_DMAC_NOINTR_COMPLETE;
	}

	return 0;
}