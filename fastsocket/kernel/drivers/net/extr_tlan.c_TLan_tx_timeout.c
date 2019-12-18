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
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_IGNORE ; 
 int /*<<< orphan*/  TLan_FreeLists (struct net_device*) ; 
 int /*<<< orphan*/  TLan_ReadAndClearStats (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_ResetAdapter (struct net_device*) ; 
 int /*<<< orphan*/  TLan_ResetLists (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void TLan_tx_timeout(struct net_device *dev)
{

	TLAN_DBG( TLAN_DEBUG_GNRL, "%s: Transmit timed out.\n", dev->name);

	/* Ok so we timed out, lets see what we can do about it...*/
	TLan_FreeLists( dev );
	TLan_ResetLists( dev );
	TLan_ReadAndClearStats( dev, TLAN_IGNORE );
	TLan_ResetAdapter( dev );
	dev->trans_start = jiffies;
	netif_wake_queue( dev );

}