#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct net_device {scalar_t__ name; } ;
struct TYPE_5__ {scalar_t__* phy; size_t phyNum; TYPE_1__* adapter; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ TLanPrivateInfo ;

/* Variables and functions */
 int TLAN_ADAPTER_UNMANAGED_PHY ; 
 scalar_t__ TLAN_PHY_MAX_ADDR ; 
 int /*<<< orphan*/  TLan_MiiReadReg (struct net_device*,scalar_t__,scalar_t__,scalar_t__*) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void TLan_PhyPrint( struct net_device *dev )
{
	TLanPrivateInfo *priv = netdev_priv(dev);
	u16 i, data0, data1, data2, data3, phy;

	phy = priv->phy[priv->phyNum];

	if ( priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY ) {
		printk( "TLAN:   Device %s, Unmanaged PHY.\n", dev->name );
	} else if ( phy <= TLAN_PHY_MAX_ADDR ) {
		printk( "TLAN:   Device %s, PHY 0x%02x.\n", dev->name, phy );
		printk( "TLAN:      Off.  +0     +1     +2     +3 \n" );
                for ( i = 0; i < 0x20; i+= 4 ) {
			printk( "TLAN:      0x%02x", i );
			TLan_MiiReadReg( dev, phy, i, &data0 );
			printk( " 0x%04hx", data0 );
			TLan_MiiReadReg( dev, phy, i + 1, &data1 );
			printk( " 0x%04hx", data1 );
			TLan_MiiReadReg( dev, phy, i + 2, &data2 );
			printk( " 0x%04hx", data2 );
			TLan_MiiReadReg( dev, phy, i + 3, &data3 );
			printk( " 0x%04hx\n", data3 );
		}
	} else {
		printk( "TLAN:   Device %s, Invalid PHY.\n", dev->name );
	}

}