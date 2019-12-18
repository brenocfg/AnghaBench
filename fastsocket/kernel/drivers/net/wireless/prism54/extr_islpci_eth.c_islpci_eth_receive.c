#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int u16 ;
struct sk_buff {unsigned char* data; int /*<<< orphan*/  truesize; int /*<<< orphan*/  len; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_12__ {scalar_t__ rssi; } ;
struct rx_annex_header {int /*<<< orphan*/  addr2; TYPE_2__ rfmon; } ;
struct rfmon_header {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_5__ stats; } ;
struct iw_quality {int updated; scalar_t__ noise; scalar_t__ level; scalar_t__ qual; } ;
struct TYPE_13__ {scalar_t__ noise; } ;
struct TYPE_14__ {TYPE_3__ qual; } ;
struct TYPE_16__ {size_t free_data_rx; scalar_t__ iw_mode; scalar_t__* pci_map_rx_address; int /*<<< orphan*/  pdev; struct sk_buff** data_low_rx; TYPE_4__ local_iwstatistics; TYPE_7__* control_block; struct net_device* ndev; } ;
typedef  TYPE_6__ islpci_private ;
struct TYPE_17__ {int /*<<< orphan*/ * driver_curr_frag; TYPE_1__* rx_data_low; } ;
typedef  TYPE_7__ isl38xx_control_block ;
struct TYPE_11__ {int /*<<< orphan*/  address; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int ETH_ALEN ; 
 size_t ISL38XX_CB_RX_DATA_LQ ; 
 size_t ISL38XX_CB_RX_QSIZE ; 
 scalar_t__ IW_MODE_MONITOR ; 
 scalar_t__ MAX_FRAGMENT_SIZE_RX ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  SHOW_BUFFER_CONTENTS ; 
 int /*<<< orphan*/  SHOW_ERROR_MESSAGES ; 
 int /*<<< orphan*/  SHOW_FUNCTION_CALLS ; 
 int /*<<< orphan*/  SHOW_TRACING ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  display_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ init_wds ; 
 int islpci_monitor_rx (TYPE_6__*,struct sk_buff**) ; 
 int /*<<< orphan*/  islpci_trigger (TYPE_6__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wireless_spy_update (struct net_device*,int /*<<< orphan*/ ,struct iw_quality*) ; 
 int /*<<< orphan*/  wmb () ; 

int
islpci_eth_receive(islpci_private *priv)
{
	struct net_device *ndev = priv->ndev;
	isl38xx_control_block *control_block = priv->control_block;
	struct sk_buff *skb;
	u16 size;
	u32 index, offset;
	unsigned char *src;
	int discard = 0;

#if VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_eth_receive \n");
#endif

	/* the device has written an Ethernet frame in the data area
	 * of the sk_buff without updating the structure, do it now */
	index = priv->free_data_rx % ISL38XX_CB_RX_QSIZE;
	size = le16_to_cpu(control_block->rx_data_low[index].size);
	skb = priv->data_low_rx[index];
	offset = ((unsigned long)
		  le32_to_cpu(control_block->rx_data_low[index].address) -
		  (unsigned long) skb->data) & 3;

#if VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_TRACING,
	      "frq->addr %x skb->data %p skb->len %u offset %u truesize %u\n ",
	      control_block->rx_data_low[priv->free_data_rx].address, skb->data,
	      skb->len, offset, skb->truesize);
#endif

	/* delete the streaming DMA mapping before processing the skb */
	pci_unmap_single(priv->pdev,
			 priv->pci_map_rx_address[index],
			 MAX_FRAGMENT_SIZE_RX + 2, PCI_DMA_FROMDEVICE);

	/* update the skb structure and allign the buffer */
	skb_put(skb, size);
	if (offset) {
		/* shift the buffer allocation offset bytes to get the right frame */
		skb_pull(skb, 2);
		skb_put(skb, 2);
	}
#if VERBOSE > SHOW_ERROR_MESSAGES
	/* display the buffer contents for debugging */
	DEBUG(SHOW_BUFFER_CONTENTS, "\nrx %p ", skb->data);
	display_buffer((char *) skb->data, skb->len);
#endif

	/* check whether WDS is enabled and whether the data frame is a WDS frame */

	if (init_wds) {
		/* WDS enabled, check for the wds address on the first 6 bytes of the buffer */
		src = skb->data + 6;
		memmove(skb->data, src, skb->len - 6);
		skb_trim(skb, skb->len - 6);
	}
#if VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_TRACING, "Fragment size %i in skb at %p\n", size, skb);
	DEBUG(SHOW_TRACING, "Skb data at %p, length %i\n", skb->data, skb->len);

	/* display the buffer contents for debugging */
	DEBUG(SHOW_BUFFER_CONTENTS, "\nrx %p ", skb->data);
	display_buffer((char *) skb->data, skb->len);
#endif
	/* take care of monitor mode and spy monitoring. */
	if (unlikely(priv->iw_mode == IW_MODE_MONITOR)) {
		skb->dev = ndev;
		discard = islpci_monitor_rx(priv, &skb);
	} else {
		if (unlikely(skb->data[2 * ETH_ALEN] == 0)) {
			/* The packet has a rx_annex. Read it for spy monitoring, Then
			 * remove it, while keeping the 2 leading MAC addr.
			 */
			struct iw_quality wstats;
			struct rx_annex_header *annex =
			    (struct rx_annex_header *) skb->data;
			wstats.level = annex->rfmon.rssi;
			/* The noise value can be a bit outdated if nobody's
			 * reading wireless stats... */
			wstats.noise = priv->local_iwstatistics.qual.noise;
			wstats.qual = wstats.level - wstats.noise;
			wstats.updated = 0x07;
			/* Update spy records */
			wireless_spy_update(ndev, annex->addr2, &wstats);

			skb_copy_from_linear_data(skb,
						  (skb->data +
						   sizeof(struct rfmon_header)),
						  2 * ETH_ALEN);
			skb_pull(skb, sizeof (struct rfmon_header));
		}
		skb->protocol = eth_type_trans(skb, ndev);
	}
	skb->ip_summed = CHECKSUM_NONE;
	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += size;

	/* deliver the skb to the network layer */
#ifdef ISLPCI_ETH_DEBUG
	printk
	    ("islpci_eth_receive:netif_rx %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X\n",
	     skb->data[0], skb->data[1], skb->data[2], skb->data[3],
	     skb->data[4], skb->data[5]);
#endif
	if (unlikely(discard)) {
		dev_kfree_skb_irq(skb);
		skb = NULL;
	} else
		netif_rx(skb);

	/* increment the read index for the rx data low queue */
	priv->free_data_rx++;

	/* add one or more sk_buff structures */
	while (index =
	       le32_to_cpu(control_block->
			   driver_curr_frag[ISL38XX_CB_RX_DATA_LQ]),
	       index - priv->free_data_rx < ISL38XX_CB_RX_QSIZE) {
		/* allocate an sk_buff for received data frames storage
		 * include any required allignment operations */
		skb = dev_alloc_skb(MAX_FRAGMENT_SIZE_RX + 2);
		if (unlikely(skb == NULL)) {
			/* error allocating an sk_buff structure elements */
			DEBUG(SHOW_ERROR_MESSAGES, "Error allocating skb \n");
			break;
		}
		skb_reserve(skb, (4 - (long) skb->data) & 0x03);
		/* store the new skb structure pointer */
		index = index % ISL38XX_CB_RX_QSIZE;
		priv->data_low_rx[index] = skb;

#if VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_TRACING,
		      "new alloc skb %p skb->data %p skb->len %u index %u truesize %u\n ",
		      skb, skb->data, skb->len, index, skb->truesize);
#endif

		/* set the streaming DMA mapping for proper PCI bus operation */
		priv->pci_map_rx_address[index] =
		    pci_map_single(priv->pdev, (void *) skb->data,
				   MAX_FRAGMENT_SIZE_RX + 2,
				   PCI_DMA_FROMDEVICE);
		if (unlikely(!priv->pci_map_rx_address[index])) {
			/* error mapping the buffer to device accessable memory address */
			DEBUG(SHOW_ERROR_MESSAGES,
			      "Error mapping DMA address\n");

			/* free the skbuf structure before aborting */
			dev_kfree_skb_irq((struct sk_buff *) skb);
			skb = NULL;
			break;
		}
		/* update the fragment address */
		control_block->rx_data_low[index].address =
			cpu_to_le32((u32)priv->pci_map_rx_address[index]);
		wmb();

		/* increment the driver read pointer */
		le32_add_cpu(&control_block->
			     driver_curr_frag[ISL38XX_CB_RX_DATA_LQ], 1);
	}

	/* trigger the device */
	islpci_trigger(priv);

	return 0;
}