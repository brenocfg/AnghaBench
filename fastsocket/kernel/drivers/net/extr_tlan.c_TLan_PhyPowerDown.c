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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__* phy; size_t phyNum; TYPE_1__* adapter; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ TLanPrivateInfo ;

/* Variables and functions */
 int HZ ; 
 int MII_GC_ISOLATE ; 
 int MII_GC_LOOPBK ; 
 int MII_GC_PDOWN ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int TLAN_ADAPTER_USE_INTERN_10 ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 scalar_t__ TLAN_PHY_NONE ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_PUP ; 
 int /*<<< orphan*/  TLan_MiiSync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_MiiWriteReg (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_SetTimer (struct net_device*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void TLan_PhyPowerDown( struct net_device *dev )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	u16		value;

	TLAN_DBG( TLAN_DEBUG_GNRL, "%s: Powering down PHY(s).\n", dev->name );
	value = MII_GC_PDOWN | MII_GC_LOOPBK | MII_GC_ISOLATE;
	TLan_MiiSync( dev->base_addr );
	TLan_MiiWriteReg( dev, priv->phy[priv->phyNum], MII_GEN_CTL, value );
	if ( ( priv->phyNum == 0 ) &&
	     ( priv->phy[1] != TLAN_PHY_NONE ) &&
	     ( ! ( priv->adapter->flags & TLAN_ADAPTER_USE_INTERN_10 ) ) ) {
		TLan_MiiSync( dev->base_addr );
		TLan_MiiWriteReg( dev, priv->phy[1], MII_GEN_CTL, value );
	}

	/* Wait for 50 ms and powerup
	 * This is abitrary.  It is intended to make sure the
	 * transceiver settles.
	 */
	TLan_SetTimer( dev, (HZ/20), TLAN_TIMER_PHY_PUP );

}