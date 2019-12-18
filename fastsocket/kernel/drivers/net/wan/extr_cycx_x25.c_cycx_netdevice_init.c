#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wan_device {int maddr; int msize; int /*<<< orphan*/  ioport; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; } ;
struct net_device {unsigned long mem_start; unsigned long mem_end; int tx_queue_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; scalar_t__ dev_addr; } ;
struct cycx_x25_channel {int /*<<< orphan*/  lcn; int /*<<< orphan*/  svc; struct cycx_device* card; } ;
struct cycx_device {struct wan_device wandev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  WAN_DISCONNECTED ; 
 int /*<<< orphan*/  cycx_x25_set_chan_state (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct cycx_x25_channel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cycx_netdevice_init(struct net_device *dev)
{
	struct cycx_x25_channel *chan = netdev_priv(dev);
	struct cycx_device *card = chan->card;
	struct wan_device *wandev = &card->wandev;

	if (!chan->svc)
		*(__be16*)dev->dev_addr = htons(chan->lcn);

	/* Initialize hardware parameters (just for reference) */
	dev->irq		= wandev->irq;
	dev->dma		= wandev->dma;
	dev->base_addr		= wandev->ioport;
	dev->mem_start		= (unsigned long)wandev->maddr;
	dev->mem_end		= (unsigned long)(wandev->maddr +
						  wandev->msize - 1);
	dev->flags		|= IFF_NOARP;

	/* Set transmit buffer queue length */
	dev->tx_queue_len	= 10;

	/* Initialize socket buffers */
	cycx_x25_set_chan_state(dev, WAN_DISCONNECTED);

	return 0;
}