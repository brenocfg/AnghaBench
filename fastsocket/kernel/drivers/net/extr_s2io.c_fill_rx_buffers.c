#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct swStat {int /*<<< orphan*/  mem_freed; int /*<<< orphan*/  pci_map_fail_cnt; int /*<<< orphan*/  mem_allocated; int /*<<< orphan*/  mem_alloc_fail_cnt; } ;
struct sk_buff {scalar_t__ truesize; void* data; } ;
struct s2io_nic {int /*<<< orphan*/  pdev; } ;
struct TYPE_16__ {int block_index; int offset; } ;
struct TYPE_13__ {int block_index; int offset; } ;
struct ring_info {int pkt_cnt; int rx_bufs_left; int rxd_count; int block_count; scalar_t__ rxd_mode; int mtu; TYPE_8__ rx_curr_put_info; int /*<<< orphan*/  pdev; struct buffAdd** ba; TYPE_7__* dev; TYPE_6__* rx_blocks; TYPE_5__ rx_curr_get_info; TYPE_3__* nic; } ;
struct buffAdd {void* ba_1; void* ba_0; } ;
struct RxD_t {unsigned long Host_Control; int Control_1; int Control_2; } ;
struct RxD3 {int Buffer0_ptr; int Buffer1_ptr; int Buffer2_ptr; } ;
struct RxD1 {int Buffer0_ptr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_14__ {struct RxD_t* block_virt_addr; TYPE_4__* rxds; } ;
struct TYPE_12__ {struct RxD_t* virt_addr; } ;
struct TYPE_10__ {TYPE_1__* stats_info; } ;
struct TYPE_11__ {TYPE_2__ mac_control; } ;
struct TYPE_9__ {struct swStat sw_stat; } ;

/* Variables and functions */
 int ALIGN_SIZE ; 
 int BUF0_LEN ; 
 int BUF1_LEN ; 
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int ENOMEM ; 
 int HEADER_802_2_SIZE ; 
 int HEADER_ETHERNET_II_802_3_SIZE ; 
 int HEADER_SNAP_SIZE ; 
 int /*<<< orphan*/  INFO_DBG ; 
 int /*<<< orphan*/  INTR_DBG ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ RXD_MODE_1 ; 
 scalar_t__ RXD_MODE_3B ; 
 int RXD_OWN_XENA ; 
 int SET_BUFFER0_SIZE_1 (int) ; 
 int SET_BUFFER0_SIZE_3 (int) ; 
 int SET_BUFFER1_SIZE_3 (int) ; 
 int SET_BUFFER2_SIZE_3 (int) ; 
 int SET_RXD_MARKER ; 
 int SUCCESS ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct RxD_t*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* pci_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rxsync_frequency ; 
 int s2BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int fill_rx_buffers(struct s2io_nic *nic, struct ring_info *ring,
			   int from_card_up)
{
	struct sk_buff *skb;
	struct RxD_t *rxdp;
	int off, size, block_no, block_no1;
	u32 alloc_tab = 0;
	u32 alloc_cnt;
	u64 tmp;
	struct buffAdd *ba;
	struct RxD_t *first_rxdp = NULL;
	u64 Buffer0_ptr = 0, Buffer1_ptr = 0;
	int rxd_index = 0;
	struct RxD1 *rxdp1;
	struct RxD3 *rxdp3;
	struct swStat *swstats = &ring->nic->mac_control.stats_info->sw_stat;

	alloc_cnt = ring->pkt_cnt - ring->rx_bufs_left;

	block_no1 = ring->rx_curr_get_info.block_index;
	while (alloc_tab < alloc_cnt) {
		block_no = ring->rx_curr_put_info.block_index;

		off = ring->rx_curr_put_info.offset;

		rxdp = ring->rx_blocks[block_no].rxds[off].virt_addr;

		rxd_index = off + 1;
		if (block_no)
			rxd_index += (block_no * ring->rxd_count);

		if ((block_no == block_no1) &&
		    (off == ring->rx_curr_get_info.offset) &&
		    (rxdp->Host_Control)) {
			DBG_PRINT(INTR_DBG, "%s: Get and Put info equated\n",
				  ring->dev->name);
			goto end;
		}
		if (off && (off == ring->rxd_count)) {
			ring->rx_curr_put_info.block_index++;
			if (ring->rx_curr_put_info.block_index ==
			    ring->block_count)
				ring->rx_curr_put_info.block_index = 0;
			block_no = ring->rx_curr_put_info.block_index;
			off = 0;
			ring->rx_curr_put_info.offset = off;
			rxdp = ring->rx_blocks[block_no].block_virt_addr;
			DBG_PRINT(INTR_DBG, "%s: Next block at: %p\n",
				  ring->dev->name, rxdp);

		}

		if ((rxdp->Control_1 & RXD_OWN_XENA) &&
		    ((ring->rxd_mode == RXD_MODE_3B) &&
		     (rxdp->Control_2 & s2BIT(0)))) {
			ring->rx_curr_put_info.offset = off;
			goto end;
		}
		/* calculate size of skb based on ring mode */
		size = ring->mtu +
			HEADER_ETHERNET_II_802_3_SIZE +
			HEADER_802_2_SIZE + HEADER_SNAP_SIZE;
		if (ring->rxd_mode == RXD_MODE_1)
			size += NET_IP_ALIGN;
		else
			size = ring->mtu + ALIGN_SIZE + BUF0_LEN + 4;

		/* allocate skb */
		skb = dev_alloc_skb(size);
		if (!skb) {
			DBG_PRINT(INFO_DBG, "%s: Could not allocate skb\n",
				  ring->dev->name);
			if (first_rxdp) {
				wmb();
				first_rxdp->Control_1 |= RXD_OWN_XENA;
			}
			swstats->mem_alloc_fail_cnt++;

			return -ENOMEM ;
		}
		swstats->mem_allocated += skb->truesize;

		if (ring->rxd_mode == RXD_MODE_1) {
			/* 1 buffer mode - normal operation mode */
			rxdp1 = (struct RxD1 *)rxdp;
			memset(rxdp, 0, sizeof(struct RxD1));
			skb_reserve(skb, NET_IP_ALIGN);
			rxdp1->Buffer0_ptr =
				pci_map_single(ring->pdev, skb->data,
					       size - NET_IP_ALIGN,
					       PCI_DMA_FROMDEVICE);
			if (pci_dma_mapping_error(nic->pdev,
						  rxdp1->Buffer0_ptr))
				goto pci_map_failed;

			rxdp->Control_2 =
				SET_BUFFER0_SIZE_1(size - NET_IP_ALIGN);
			rxdp->Host_Control = (unsigned long)skb;
		} else if (ring->rxd_mode == RXD_MODE_3B) {
			/*
			 * 2 buffer mode -
			 * 2 buffer mode provides 128
			 * byte aligned receive buffers.
			 */

			rxdp3 = (struct RxD3 *)rxdp;
			/* save buffer pointers to avoid frequent dma mapping */
			Buffer0_ptr = rxdp3->Buffer0_ptr;
			Buffer1_ptr = rxdp3->Buffer1_ptr;
			memset(rxdp, 0, sizeof(struct RxD3));
			/* restore the buffer pointers for dma sync*/
			rxdp3->Buffer0_ptr = Buffer0_ptr;
			rxdp3->Buffer1_ptr = Buffer1_ptr;

			ba = &ring->ba[block_no][off];
			skb_reserve(skb, BUF0_LEN);
			tmp = (u64)(unsigned long)skb->data;
			tmp += ALIGN_SIZE;
			tmp &= ~ALIGN_SIZE;
			skb->data = (void *) (unsigned long)tmp;
			skb_reset_tail_pointer(skb);

			if (from_card_up) {
				rxdp3->Buffer0_ptr =
					pci_map_single(ring->pdev, ba->ba_0,
						       BUF0_LEN,
						       PCI_DMA_FROMDEVICE);
				if (pci_dma_mapping_error(nic->pdev,
							  rxdp3->Buffer0_ptr))
					goto pci_map_failed;
			} else
				pci_dma_sync_single_for_device(ring->pdev,
							       (dma_addr_t)rxdp3->Buffer0_ptr,
							       BUF0_LEN,
							       PCI_DMA_FROMDEVICE);

			rxdp->Control_2 = SET_BUFFER0_SIZE_3(BUF0_LEN);
			if (ring->rxd_mode == RXD_MODE_3B) {
				/* Two buffer mode */

				/*
				 * Buffer2 will have L3/L4 header plus
				 * L4 payload
				 */
				rxdp3->Buffer2_ptr = pci_map_single(ring->pdev,
								    skb->data,
								    ring->mtu + 4,
								    PCI_DMA_FROMDEVICE);

				if (pci_dma_mapping_error(nic->pdev,
							  rxdp3->Buffer2_ptr))
					goto pci_map_failed;

				if (from_card_up) {
					rxdp3->Buffer1_ptr =
						pci_map_single(ring->pdev,
							       ba->ba_1,
							       BUF1_LEN,
							       PCI_DMA_FROMDEVICE);

					if (pci_dma_mapping_error(nic->pdev,
								  rxdp3->Buffer1_ptr)) {
						pci_unmap_single(ring->pdev,
								 (dma_addr_t)(unsigned long)
								 skb->data,
								 ring->mtu + 4,
								 PCI_DMA_FROMDEVICE);
						goto pci_map_failed;
					}
				}
				rxdp->Control_2 |= SET_BUFFER1_SIZE_3(1);
				rxdp->Control_2 |= SET_BUFFER2_SIZE_3
					(ring->mtu + 4);
			}
			rxdp->Control_2 |= s2BIT(0);
			rxdp->Host_Control = (unsigned long) (skb);
		}
		if (alloc_tab & ((1 << rxsync_frequency) - 1))
			rxdp->Control_1 |= RXD_OWN_XENA;
		off++;
		if (off == (ring->rxd_count + 1))
			off = 0;
		ring->rx_curr_put_info.offset = off;

		rxdp->Control_2 |= SET_RXD_MARKER;
		if (!(alloc_tab & ((1 << rxsync_frequency) - 1))) {
			if (first_rxdp) {
				wmb();
				first_rxdp->Control_1 |= RXD_OWN_XENA;
			}
			first_rxdp = rxdp;
		}
		ring->rx_bufs_left += 1;
		alloc_tab++;
	}

end:
	/* Transfer ownership of first descriptor to adapter just before
	 * exiting. Before that, use memory barrier so that ownership
	 * and other fields are seen by adapter correctly.
	 */
	if (first_rxdp) {
		wmb();
		first_rxdp->Control_1 |= RXD_OWN_XENA;
	}

	return SUCCESS;

pci_map_failed:
	swstats->pci_map_fail_cnt++;
	swstats->mem_freed += skb->truesize;
	dev_kfree_skb_irq(skb);
	return -ENOMEM;
}