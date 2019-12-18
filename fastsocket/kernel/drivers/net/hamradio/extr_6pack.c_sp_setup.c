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
struct net_device {int tx_queue_len; scalar_t__ flags; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_AX25 ; 
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 int /*<<< orphan*/  AX25_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  SIXP_MTU ; 
 int /*<<< orphan*/  ax25_bcast ; 
 int /*<<< orphan*/  ax25_defaddr ; 
 int /*<<< orphan*/  free_netdev ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp_header_ops ; 
 int /*<<< orphan*/  sp_netdev_ops ; 

__attribute__((used)) static void sp_setup(struct net_device *dev)
{
	/* Finish setting up the DEVICE info. */
	dev->netdev_ops		= &sp_netdev_ops;
	dev->destructor		= free_netdev;
	dev->mtu		= SIXP_MTU;
	dev->hard_header_len	= AX25_MAX_HEADER_LEN;
	dev->header_ops 	= &sp_header_ops;

	dev->addr_len		= AX25_ADDR_LEN;
	dev->type		= ARPHRD_AX25;
	dev->tx_queue_len	= 10;

	/* Only activated in AX.25 mode */
	memcpy(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	memcpy(dev->dev_addr, &ax25_defaddr, AX25_ADDR_LEN);

	dev->flags		= 0;
}