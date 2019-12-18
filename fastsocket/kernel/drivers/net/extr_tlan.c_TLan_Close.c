#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; scalar_t__ base_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * function; } ;
struct TYPE_4__ {TYPE_3__ timer; scalar_t__ neg_be_verbose; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_HC_AD_RST ; 
 scalar_t__ TLAN_HOST_CMD ; 
 int /*<<< orphan*/  TLAN_RECORD ; 
 int /*<<< orphan*/  TLan_FreeLists (struct net_device*) ; 
 int /*<<< orphan*/  TLan_ReadAndClearStats (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int TLan_Close(struct net_device *dev)
{
	TLanPrivateInfo *priv = netdev_priv(dev);

	netif_stop_queue(dev);
	priv->neg_be_verbose = 0;

	TLan_ReadAndClearStats( dev, TLAN_RECORD );
	outl( TLAN_HC_AD_RST, dev->base_addr + TLAN_HOST_CMD );
	if ( priv->timer.function != NULL ) {
		del_timer_sync( &priv->timer );
		priv->timer.function = NULL;
	}

	free_irq( dev->irq, dev );
	TLan_FreeLists( dev );
	TLAN_DBG( TLAN_DEBUG_GNRL, "Device %s closed.\n", dev->name );

	return 0;

}