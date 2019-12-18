#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  tlanRev; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_DEF_REVISION ; 
 int /*<<< orphan*/  TLAN_IGNORE ; 
 int /*<<< orphan*/  TLan_DioRead8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_HandleInterrupt ; 
 int /*<<< orphan*/  TLan_ReadAndClearStats (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_ResetAdapter (struct net_device*) ; 
 int /*<<< orphan*/  TLan_ResetLists (struct net_device*) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int TLan_Open( struct net_device *dev )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	int		err;

	priv->tlanRev = TLan_DioRead8( dev->base_addr, TLAN_DEF_REVISION );
	err = request_irq( dev->irq, TLan_HandleInterrupt, IRQF_SHARED,
			   dev->name, dev );

	if ( err ) {
		pr_err("TLAN:  Cannot open %s because IRQ %d is already in use.\n",
		       dev->name, dev->irq );
		return err;
	}

	init_timer(&priv->timer);
	netif_start_queue(dev);

	/* NOTE: It might not be necessary to read the stats before a
			 reset if you don't care what the values are.
	*/
	TLan_ResetLists( dev );
	TLan_ReadAndClearStats( dev, TLAN_IGNORE );
	TLan_ResetAdapter( dev );

	TLAN_DBG( TLAN_DEBUG_GNRL, "%s: Opened.  TLAN Chip Rev: %x\n",
		  dev->name, priv->tlanRev );

	return 0;

}