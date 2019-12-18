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
struct ipw2100_rx_packet {TYPE_1__* skb; int /*<<< orphan*/  dma_addr; struct ipw2100_rx* rxp; } ;
struct ipw2100_rx {int dummy; } ;
struct ipw2100_priv {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 TYPE_1__* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw2100_alloc_skb(struct ipw2100_priv *priv,
				    struct ipw2100_rx_packet *packet)
{
	packet->skb = dev_alloc_skb(sizeof(struct ipw2100_rx));
	if (!packet->skb)
		return -ENOMEM;

	packet->rxp = (struct ipw2100_rx *)packet->skb->data;
	packet->dma_addr = pci_map_single(priv->pci_dev, packet->skb->data,
					  sizeof(struct ipw2100_rx),
					  PCI_DMA_FROMDEVICE);
	/* NOTE: pci_map_single does not return an error code, and 0 is a valid
	 *       dma_addr */

	return 0;
}