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
struct net_device {int tx_queue_len; int hard_header_len; int addr_len; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * header_ops; scalar_t__* dev_addr; scalar_t__ broadcast; int /*<<< orphan*/  type; int /*<<< orphan*/  mtu; scalar_t__ flags; scalar_t__ trans_start; } ;
typedef  int /*<<< orphan*/  STRIP_Header ;
typedef  int /*<<< orphan*/  MetricomAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_METRICOM ; 
 int /*<<< orphan*/  DEFAULT_STRIP_MTU ; 
 int /*<<< orphan*/  broadcast_address ; 
 int /*<<< orphan*/  strip_header_ops ; 
 int /*<<< orphan*/  strip_netdev_ops ; 

__attribute__((used)) static void strip_dev_setup(struct net_device *dev)
{
	/*
	 * Finish setting up the DEVICE info.
	 */

	dev->trans_start = 0;
	dev->tx_queue_len = 30;	/* Drop after 30 frames queued */

	dev->flags = 0;
	dev->mtu = DEFAULT_STRIP_MTU;
	dev->type = ARPHRD_METRICOM;	/* dtang */
	dev->hard_header_len = sizeof(STRIP_Header);
	/*
	 *  netdev_priv(dev) Already holds a pointer to our struct strip
	 */

	*(MetricomAddress *)dev->broadcast = broadcast_address;
	dev->dev_addr[0] = 0;
	dev->addr_len = sizeof(MetricomAddress);

	dev->header_ops = &strip_header_ops,
	dev->netdev_ops = &strip_netdev_ops;
}