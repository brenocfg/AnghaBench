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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  ip_summed; struct net_device* dev; int /*<<< orphan*/  tail; int /*<<< orphan*/  protocol; } ;
struct sh_eth_rxdesc {int status; int /*<<< orphan*/  addr; int /*<<< orphan*/  buffer_length; scalar_t__ frame_length; } ;
struct TYPE_4__ {scalar_t__ rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct sh_eth_private {int cur_rx; int dirty_rx; int /*<<< orphan*/  rx_buf_sz; struct sk_buff** rx_skbuff; struct sh_eth_rxdesc* rx_ring; TYPE_2__ stats; TYPE_1__* cd; } ;
struct net_device {scalar_t__ base_addr; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_swap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ EDRRR ; 
 int EDRRR_R ; 
 int /*<<< orphan*/  PTR_ALIGN (int /*<<< orphan*/ ,int) ; 
 int RDFEND ; 
 int RD_RACT ; 
 int RD_RDEL ; 
 int RD_RFP ; 
 int RD_RFS1 ; 
 int RD_RFS10 ; 
 int RD_RFS2 ; 
 int RD_RFS3 ; 
 int RD_RFS4 ; 
 int RD_RFS5 ; 
 int RD_RFS6 ; 
 int RX_RING_SIZE ; 
 int cpu_to_edmac (struct sh_eth_private*,int) ; 
 int ctrl_inl (scalar_t__) ; 
 int /*<<< orphan*/  ctrl_outl (int,scalar_t__) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int edmac_to_cpu (struct sh_eth_private*,int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_set_receive_align (struct sk_buff*) ; 
 int /*<<< orphan*/  sh_eth_soft_swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_eth_rx(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_rxdesc *rxdesc;

	int entry = mdp->cur_rx % RX_RING_SIZE;
	int boguscnt = (mdp->dirty_rx + RX_RING_SIZE) - mdp->cur_rx;
	struct sk_buff *skb;
	u16 pkt_len = 0;
	u32 desc_status;

	rxdesc = &mdp->rx_ring[entry];
	while (!(rxdesc->status & cpu_to_edmac(mdp, RD_RACT))) {
		desc_status = edmac_to_cpu(mdp, rxdesc->status);
		pkt_len = rxdesc->frame_length;

		if (--boguscnt < 0)
			break;

		if (!(desc_status & RDFEND))
			mdp->stats.rx_length_errors++;

		if (desc_status & (RD_RFS1 | RD_RFS2 | RD_RFS3 | RD_RFS4 |
				   RD_RFS5 | RD_RFS6 | RD_RFS10)) {
			mdp->stats.rx_errors++;
			if (desc_status & RD_RFS1)
				mdp->stats.rx_crc_errors++;
			if (desc_status & RD_RFS2)
				mdp->stats.rx_frame_errors++;
			if (desc_status & RD_RFS3)
				mdp->stats.rx_length_errors++;
			if (desc_status & RD_RFS4)
				mdp->stats.rx_length_errors++;
			if (desc_status & RD_RFS6)
				mdp->stats.rx_missed_errors++;
			if (desc_status & RD_RFS10)
				mdp->stats.rx_over_errors++;
		} else {
			if (!mdp->cd->hw_swap)
				sh_eth_soft_swap(
					phys_to_virt(ALIGN(rxdesc->addr, 4)),
					pkt_len + 2);
			skb = mdp->rx_skbuff[entry];
			mdp->rx_skbuff[entry] = NULL;
			skb_put(skb, pkt_len);
			skb->protocol = eth_type_trans(skb, ndev);
			netif_rx(skb);
			mdp->stats.rx_packets++;
			mdp->stats.rx_bytes += pkt_len;
		}
		rxdesc->status |= cpu_to_edmac(mdp, RD_RACT);
		entry = (++mdp->cur_rx) % RX_RING_SIZE;
		rxdesc = &mdp->rx_ring[entry];
	}

	/* Refill the Rx ring buffers. */
	for (; mdp->cur_rx - mdp->dirty_rx > 0; mdp->dirty_rx++) {
		entry = mdp->dirty_rx % RX_RING_SIZE;
		rxdesc = &mdp->rx_ring[entry];
		/* The size of the buffer is 16 byte boundary. */
		rxdesc->buffer_length = ALIGN(mdp->rx_buf_sz, 16);

		if (mdp->rx_skbuff[entry] == NULL) {
			skb = dev_alloc_skb(mdp->rx_buf_sz);
			mdp->rx_skbuff[entry] = skb;
			if (skb == NULL)
				break;	/* Better luck next round. */
			dma_map_single(&ndev->dev, skb->tail, mdp->rx_buf_sz,
					DMA_FROM_DEVICE);
			skb->dev = ndev;
			sh_eth_set_receive_align(skb);

			skb->ip_summed = CHECKSUM_NONE;
			rxdesc->addr = virt_to_phys(PTR_ALIGN(skb->data, 4));
		}
		if (entry >= RX_RING_SIZE - 1)
			rxdesc->status |=
				cpu_to_edmac(mdp, RD_RACT | RD_RFP | RD_RDEL);
		else
			rxdesc->status |=
				cpu_to_edmac(mdp, RD_RACT | RD_RFP);
	}

	/* Restart Rx engine if stopped. */
	/* If we don't need to check status, don't. -KDU */
	if (!(ctrl_inl(ndev->base_addr + EDRRR) & EDRRR_R))
		ctrl_outl(EDRRR_R, ndev->base_addr + EDRRR);

	return 0;
}