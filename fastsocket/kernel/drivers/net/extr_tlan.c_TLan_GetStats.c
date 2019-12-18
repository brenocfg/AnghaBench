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
struct net_device_stats {int dummy; } ;
struct net_device {struct net_device_stats stats; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ txList; scalar_t__ rxList; int /*<<< orphan*/  txBusyCount; int /*<<< orphan*/  rxEocCount; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLAN_DEBUG_GNRL ; 
 int TLAN_DEBUG_LIST ; 
 int /*<<< orphan*/  TLAN_DEBUG_RX ; 
 int /*<<< orphan*/  TLAN_DEBUG_TX ; 
 int TLAN_NUM_RX_LISTS ; 
 int TLAN_NUM_TX_LISTS ; 
 int /*<<< orphan*/  TLAN_RECORD ; 
 int /*<<< orphan*/  TLan_PhyPrint (struct net_device*) ; 
 int /*<<< orphan*/  TLan_PrintDio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_PrintList (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  TLan_ReadAndClearStats (struct net_device*,int /*<<< orphan*/ ) ; 
 int debug ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *TLan_GetStats( struct net_device *dev )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	int i;

	/* Should only read stats if open ? */
	TLan_ReadAndClearStats( dev, TLAN_RECORD );

	TLAN_DBG( TLAN_DEBUG_RX, "RECEIVE:  %s EOC count = %d\n", dev->name,
		  priv->rxEocCount );
	TLAN_DBG( TLAN_DEBUG_TX, "TRANSMIT:  %s Busy count = %d\n", dev->name,
		  priv->txBusyCount );
	if ( debug & TLAN_DEBUG_GNRL ) {
		TLan_PrintDio( dev->base_addr );
		TLan_PhyPrint( dev );
	}
	if ( debug & TLAN_DEBUG_LIST ) {
		for ( i = 0; i < TLAN_NUM_RX_LISTS; i++ )
			TLan_PrintList( priv->rxList + i, "RX", i );
		for ( i = 0; i < TLAN_NUM_TX_LISTS; i++ )
			TLan_PrintList( priv->txList + i, "TX", i );
	}

	return &dev->stats;

}