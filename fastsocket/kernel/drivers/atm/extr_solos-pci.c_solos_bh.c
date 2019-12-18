#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct solos_card {int nr_ports; int buffer_size; scalar_t__ config_regs; int /*<<< orphan*/  tlet; TYPE_2__* dev; struct sk_buff** rx_skb; scalar_t__* atmdev; scalar_t__ using_dma; int /*<<< orphan*/  cli_queue_lock; int /*<<< orphan*/ * cli_queue; } ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;
struct pkt_hdr {int /*<<< orphan*/  vpi; int /*<<< orphan*/  vci; int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct atm_vcc {TYPE_1__* stats; int /*<<< orphan*/  (* push ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct TYPE_7__ {int dma_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 scalar_t__ FLAGS_ADDR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
#define  PKT_COMMAND 130 
#define  PKT_DATA 129 
#define  PKT_STATUS 128 
 scalar_t__ RX_BUF (struct solos_card*,int) ; 
 scalar_t__ RX_DMA_ADDR (int) ; 
 int RX_DMA_SIZE ; 
 TYPE_4__* SKB_CB (struct sk_buff*) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_charge (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 scalar_t__ atmdebug ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 struct atm_vcc* find_vcc (scalar_t__,int,int) ; 
 int fpga_tx (struct solos_card*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (struct pkt_hdr*,scalar_t__,int) ; 
 scalar_t__ net_ratelimit () ; 
 int pci_map_single (TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_buffer (struct sk_buff*) ; 
 int /*<<< orphan*/  process_command (struct solos_card*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  process_status (struct solos_card*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct pkt_hdr* skb_put (struct sk_buff*,int) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void solos_bh(unsigned long card_arg)
{
	struct solos_card *card = (void *)card_arg;
	uint32_t card_flags;
	uint32_t rx_done = 0;
	int port;

	/*
	 * Since fpga_tx() is going to need to read the flags under its lock,
	 * it can return them to us so that we don't have to hit PCI MMIO
	 * again for the same information
	 */
	card_flags = fpga_tx(card);

	for (port = 0; port < card->nr_ports; port++) {
		if (card_flags & (0x10 << port)) {
			struct pkt_hdr _hdr, *header;
			struct sk_buff *skb;
			struct atm_vcc *vcc;
			int size;

			if (card->using_dma) {
				skb = card->rx_skb[port];
				card->rx_skb[port] = NULL;

				pci_unmap_single(card->dev, SKB_CB(skb)->dma_addr,
						 RX_DMA_SIZE, PCI_DMA_FROMDEVICE);

				header = (void *)skb->data;
				size = le16_to_cpu(header->size);
				skb_put(skb, size + sizeof(*header));
				skb_pull(skb, sizeof(*header));
			} else {
				header = &_hdr;

				rx_done |= 0x10 << port;

				memcpy_fromio(header, RX_BUF(card, port), sizeof(*header));

				size = le16_to_cpu(header->size);
				if (size > (card->buffer_size - sizeof(*header))){
					dev_warn(&card->dev->dev, "Invalid buffer size\n");
					continue;
				}

				skb = alloc_skb(size + 1, GFP_ATOMIC);
				if (!skb) {
					if (net_ratelimit())
						dev_warn(&card->dev->dev, "Failed to allocate sk_buff for RX\n");
					continue;
				}

				memcpy_fromio(skb_put(skb, size),
					      RX_BUF(card, port) + sizeof(*header),
					      size);
			}
			if (atmdebug) {
				dev_info(&card->dev->dev, "Received: device %d\n", port);
				dev_info(&card->dev->dev, "size: %d VPI: %d VCI: %d\n",
					 size, le16_to_cpu(header->vpi),
					 le16_to_cpu(header->vci));
				print_buffer(skb);
			}

			switch (le16_to_cpu(header->type)) {
			case PKT_DATA:
				vcc = find_vcc(card->atmdev[port], le16_to_cpu(header->vpi),
					       le16_to_cpu(header->vci));
				if (!vcc) {
					if (net_ratelimit())
						dev_warn(&card->dev->dev, "Received packet for unknown VCI.VPI %d.%d on port %d\n",
							 le16_to_cpu(header->vci), le16_to_cpu(header->vpi),
							 port);
					continue;
				}
				atm_charge(vcc, skb->truesize);
				vcc->push(vcc, skb);
				atomic_inc(&vcc->stats->rx);
				break;

			case PKT_STATUS:
				if (process_status(card, port, skb) &&
				    net_ratelimit()) {
					dev_warn(&card->dev->dev, "Bad status packet of %d bytes on port %d:\n", skb->len, port);
					print_buffer(skb);
				}
				dev_kfree_skb_any(skb);
				break;

			case PKT_COMMAND:
			default: /* FIXME: Not really, surely? */
				if (process_command(card, port, skb))
					break;
				spin_lock(&card->cli_queue_lock);
				if (skb_queue_len(&card->cli_queue[port]) > 10) {
					if (net_ratelimit())
						dev_warn(&card->dev->dev, "Dropping console response on port %d\n",
							 port);
					dev_kfree_skb_any(skb);
				} else
					skb_queue_tail(&card->cli_queue[port], skb);
				spin_unlock(&card->cli_queue_lock);
				break;
			}
		}
		/* Allocate RX skbs for any ports which need them */
		if (card->using_dma && card->atmdev[port] &&
		    !card->rx_skb[port]) {
			struct sk_buff *skb = alloc_skb(RX_DMA_SIZE, GFP_ATOMIC);
			if (skb) {
				SKB_CB(skb)->dma_addr =
					pci_map_single(card->dev, skb->data,
						       RX_DMA_SIZE, PCI_DMA_FROMDEVICE);
				iowrite32(SKB_CB(skb)->dma_addr,
					  card->config_regs + RX_DMA_ADDR(port));
				card->rx_skb[port] = skb;
			} else {
				if (net_ratelimit())
					dev_warn(&card->dev->dev, "Failed to allocate RX skb");

				/* We'll have to try again later */
				tasklet_schedule(&card->tlet);
			}
		}
	}
	if (rx_done)
		iowrite32(rx_done, card->config_regs + FLAGS_ADDR);

	return;
}