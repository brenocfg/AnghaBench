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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int* phy; size_t phyNum; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int HZ ; 
 int MII_GC_LOOPBK ; 
 int MII_GC_RESET ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_START_LINK ; 
 int /*<<< orphan*/  TLan_MiiReadReg (struct net_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TLan_MiiSync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_MiiWriteReg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_SetTimer (struct net_device*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void TLan_PhyReset( struct net_device *dev )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	u16		phy;
	u16		value;

	phy = priv->phy[priv->phyNum];

	TLAN_DBG( TLAN_DEBUG_GNRL, "%s: Reseting PHY.\n", dev->name );
	TLan_MiiSync( dev->base_addr );
	value = MII_GC_LOOPBK | MII_GC_RESET;
	TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, value );
	TLan_MiiReadReg( dev, phy, MII_GEN_CTL, &value );
	while ( value & MII_GC_RESET ) {
		TLan_MiiReadReg( dev, phy, MII_GEN_CTL, &value );
	}

	/* Wait for 500 ms and initialize.
	 * I don't remember why I wait this long.
	 * I've changed this to 50ms, as it seems long enough.
	 */
	TLan_SetTimer( dev, (HZ/20), TLAN_TIMER_PHY_START_LINK );

}