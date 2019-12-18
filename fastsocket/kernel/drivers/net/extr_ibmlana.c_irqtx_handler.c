#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ length; } ;
typedef  TYPE_2__ tda_t ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_8__ {int currtxdescr; scalar_t__ txusedcnt; scalar_t__* txused; scalar_t__ tdastart; scalar_t__ base; } ;
typedef  TYPE_3__ ibmlana_priv ;

/* Variables and functions */
 int /*<<< orphan*/  StartTx (struct net_device*,int) ; 
 int TXBUFCNT ; 
 int /*<<< orphan*/  memcpy_fromio (TYPE_2__*,scalar_t__,int) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void irqtx_handler(struct net_device *dev)
{
	ibmlana_priv *priv = netdev_priv(dev);
	tda_t tda;

	/* fetch descriptor (we forgot the size ;-) */
	memcpy_fromio(&tda, priv->base + priv->tdastart + (priv->currtxdescr * sizeof(tda_t)), sizeof(tda_t));

	/* update statistics */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += tda.length;

	/* update our pointers */
	priv->txused[priv->currtxdescr] = 0;
	priv->txusedcnt--;

	/* if there are more descriptors present in RAM, start them */
	if (priv->txusedcnt > 0)
		StartTx(dev, (priv->currtxdescr + 1) % TXBUFCNT);

	/* tell the upper layer we can go on transmitting */
	netif_wake_queue(dev);
}