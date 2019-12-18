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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct ks8695_priv {int next_rx_desc_read; TYPE_3__* rx_ring; TYPE_1__* rx_buffers; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int status; scalar_t__ data_ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  dma_ptr; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KS8695_DRSC ; 
 int MAX_RX_DESC_MASK ; 
 int RDES_CE ; 
 int RDES_ES ; 
 int RDES_FLEN ; 
 int RDES_FS ; 
 int RDES_LS ; 
 int /*<<< orphan*/  RDES_OWN ; 
 int RDES_RE ; 
 int RDES_RF ; 
 int RDES_TL ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  ks8695_refill_rxbuffers (struct ks8695_priv*) ; 
 int /*<<< orphan*/  ks8695_writereg (struct ks8695_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 scalar_t__ likely (int) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static irqreturn_t
ks8695_rx_irq(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct ks8695_priv *ksp = netdev_priv(ndev);
	struct sk_buff *skb;
	int buff_n;
	u32 flags;
	int pktlen;
	int last_rx_processed = -1;

	buff_n = ksp->next_rx_desc_read;
	do {
		if (ksp->rx_buffers[buff_n].skb &&
		    !(ksp->rx_ring[buff_n].status & cpu_to_le32(RDES_OWN))) {
			rmb();
			flags = le32_to_cpu(ksp->rx_ring[buff_n].status);
			/* Found an SKB which we own, this means we
			 * received a packet
			 */
			if ((flags & (RDES_FS | RDES_LS)) !=
			    (RDES_FS | RDES_LS)) {
				/* This packet is not the first and
				 * the last segment.  Therefore it is
				 * a "spanning" packet and we can't
				 * handle it
				 */
				goto rx_failure;
			}

			if (flags & (RDES_ES | RDES_RE)) {
				/* It's an error packet */
				ndev->stats.rx_errors++;
				if (flags & RDES_TL)
					ndev->stats.rx_length_errors++;
				if (flags & RDES_RF)
					ndev->stats.rx_length_errors++;
				if (flags & RDES_CE)
					ndev->stats.rx_crc_errors++;
				if (flags & RDES_RE)
					ndev->stats.rx_missed_errors++;

				goto rx_failure;
			}

			pktlen = flags & RDES_FLEN;
			pktlen -= 4; /* Drop the CRC */

			/* Retrieve the sk_buff */
			skb = ksp->rx_buffers[buff_n].skb;

			/* Clear it from the ring */
			ksp->rx_buffers[buff_n].skb = NULL;
			ksp->rx_ring[buff_n].data_ptr = 0;

			/* Unmap the SKB */
			dma_unmap_single(ksp->dev,
					 ksp->rx_buffers[buff_n].dma_ptr,
					 ksp->rx_buffers[buff_n].length,
					 DMA_FROM_DEVICE);

			/* Relinquish the SKB to the network layer */
			skb_put(skb, pktlen);
			skb->protocol = eth_type_trans(skb, ndev);
			netif_rx(skb);

			/* Record stats */
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += pktlen;
			goto rx_finished;

rx_failure:
			/* This ring entry is an error, but we can
			 * re-use the skb
			 */
			/* Give the ring entry back to the hardware */
			ksp->rx_ring[buff_n].status = cpu_to_le32(RDES_OWN);
rx_finished:
			/* And note this as processed so we can start
			 * from here next time
			 */
			last_rx_processed = buff_n;
		} else {
			/* Ran out of things to process, stop now */
			break;
		}
		buff_n = (buff_n + 1) & MAX_RX_DESC_MASK;
	} while (buff_n != ksp->next_rx_desc_read);

	/* And note which RX descriptor we last did anything with */
	if (likely(last_rx_processed != -1))
		ksp->next_rx_desc_read =
			(last_rx_processed + 1) & MAX_RX_DESC_MASK;

	/* And refill the buffers */
	ks8695_refill_rxbuffers(ksp);

	/* Kick the RX DMA engine, in case it became suspended */
	ks8695_writereg(ksp, KS8695_DRSC, 0);

	return IRQ_HANDLED;
}