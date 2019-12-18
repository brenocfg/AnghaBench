#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_10__ {size_t tx_in; TYPE_2__* card; struct sk_buff** tx_skbs; struct net_device* dev; } ;
typedef  TYPE_3__ port_t ;
struct TYPE_11__ {int stat; int /*<<< orphan*/  address; } ;
typedef  TYPE_4__ desc_t ;
struct TYPE_12__ {TYPE_4__* tx_descs; } ;
struct TYPE_9__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
#define  PACKET_EMPTY 130 
#define  PACKET_FULL 129 
#define  PACKET_UNDERRUN 128 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_BUFFERS ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 TYPE_6__* get_status (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wanxl_tx_intr(port_t *port)
{
	struct net_device *dev = port->dev;
	while (1) {
                desc_t *desc = &get_status(port)->tx_descs[port->tx_in];
		struct sk_buff *skb = port->tx_skbs[port->tx_in];

		switch (desc->stat) {
		case PACKET_FULL:
		case PACKET_EMPTY:
			netif_wake_queue(dev);
			return;

		case PACKET_UNDERRUN:
			dev->stats.tx_errors++;
			dev->stats.tx_fifo_errors++;
			break;

		default:
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += skb->len;
		}
                desc->stat = PACKET_EMPTY; /* Free descriptor */
		pci_unmap_single(port->card->pdev, desc->address, skb->len,
				 PCI_DMA_TODEVICE);
		dev_kfree_skb_irq(skb);
                port->tx_in = (port->tx_in + 1) % TX_BUFFERS;
        }
}