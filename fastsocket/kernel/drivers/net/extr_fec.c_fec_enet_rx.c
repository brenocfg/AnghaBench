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
typedef  int ushort ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct fec_enet_private {int /*<<< orphan*/  hw_lock; struct bufdesc* cur_rx; scalar_t__ hwp; struct bufdesc* rx_bd_base; int /*<<< orphan*/  opened; } ;
struct bufdesc {unsigned short cbd_sc; int cbd_datlen; int /*<<< orphan*/  cbd_bufaddr; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 unsigned short BD_ENET_RX_CL ; 
 unsigned short BD_ENET_RX_CR ; 
 unsigned short BD_ENET_RX_EMPTY ; 
 unsigned short BD_ENET_RX_LAST ; 
 unsigned short BD_ENET_RX_LG ; 
 unsigned short BD_ENET_RX_NO ; 
 unsigned short BD_ENET_RX_OV ; 
 unsigned short BD_ENET_RX_SH ; 
 unsigned short BD_ENET_RX_STATS ; 
 unsigned short BD_ENET_RX_WRAP ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ FEC_R_DES_ACTIVE ; 
 int NET_IP_ALIGN ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
fec_enet_rx(struct net_device *dev)
{
	struct	fec_enet_private *fep = netdev_priv(dev);
	struct bufdesc *bdp;
	unsigned short status;
	struct	sk_buff	*skb;
	ushort	pkt_len;
	__u8 *data;

#ifdef CONFIG_M532x
	flush_cache_all();
#endif

	spin_lock(&fep->hw_lock);

	/* First, grab all of the stats for the incoming packet.
	 * These get messed up if we get called due to a busy condition.
	 */
	bdp = fep->cur_rx;

	while (!((status = bdp->cbd_sc) & BD_ENET_RX_EMPTY)) {

		/* Since we have allocated space to hold a complete frame,
		 * the last indicator should be set.
		 */
		if ((status & BD_ENET_RX_LAST) == 0)
			printk("FEC ENET: rcv is not +last\n");

		if (!fep->opened)
			goto rx_processing_done;

		/* Check for errors. */
		if (status & (BD_ENET_RX_LG | BD_ENET_RX_SH | BD_ENET_RX_NO |
			   BD_ENET_RX_CR | BD_ENET_RX_OV)) {
			dev->stats.rx_errors++;
			if (status & (BD_ENET_RX_LG | BD_ENET_RX_SH)) {
				/* Frame too long or too short. */
				dev->stats.rx_length_errors++;
			}
			if (status & BD_ENET_RX_NO)	/* Frame alignment */
				dev->stats.rx_frame_errors++;
			if (status & BD_ENET_RX_CR)	/* CRC Error */
				dev->stats.rx_crc_errors++;
			if (status & BD_ENET_RX_OV)	/* FIFO overrun */
				dev->stats.rx_fifo_errors++;
		}

		/* Report late collisions as a frame error.
		 * On this error, the BD is closed, but we don't know what we
		 * have in the buffer.  So, just drop this frame on the floor.
		 */
		if (status & BD_ENET_RX_CL) {
			dev->stats.rx_errors++;
			dev->stats.rx_frame_errors++;
			goto rx_processing_done;
		}

		/* Process the incoming frame. */
		dev->stats.rx_packets++;
		pkt_len = bdp->cbd_datlen;
		dev->stats.rx_bytes += pkt_len;
		data = (__u8*)__va(bdp->cbd_bufaddr);

	        dma_unmap_single(NULL, bdp->cbd_bufaddr, bdp->cbd_datlen,
        			DMA_FROM_DEVICE);

		/* This does 16 byte alignment, exactly what we need.
		 * The packet length includes FCS, but we don't want to
		 * include that when passing upstream as it messes up
		 * bridging applications.
		 */
		skb = dev_alloc_skb(pkt_len - 4 + NET_IP_ALIGN);

		if (unlikely(!skb)) {
			printk("%s: Memory squeeze, dropping packet.\n",
					dev->name);
			dev->stats.rx_dropped++;
		} else {
			skb_reserve(skb, NET_IP_ALIGN);
			skb_put(skb, pkt_len - 4);	/* Make room */
			skb_copy_to_linear_data(skb, data, pkt_len - 4);
			skb->protocol = eth_type_trans(skb, dev);
			netif_rx(skb);
		}

        	bdp->cbd_bufaddr = dma_map_single(NULL, data, bdp->cbd_datlen,
			DMA_FROM_DEVICE);
rx_processing_done:
		/* Clear the status flags for this buffer */
		status &= ~BD_ENET_RX_STATS;

		/* Mark the buffer empty */
		status |= BD_ENET_RX_EMPTY;
		bdp->cbd_sc = status;

		/* Update BD pointer to next entry */
		if (status & BD_ENET_RX_WRAP)
			bdp = fep->rx_bd_base;
		else
			bdp++;
		/* Doing this here will keep the FEC running while we process
		 * incoming frames.  On a heavily loaded network, we should be
		 * able to keep up at the expense of system resources.
		 */
		writel(0, fep->hwp + FEC_R_DES_ACTIVE);
	}
	fep->cur_rx = bdp;

	spin_unlock(&fep->hw_lock);
}