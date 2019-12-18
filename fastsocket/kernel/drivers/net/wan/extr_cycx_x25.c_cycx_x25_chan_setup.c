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
struct net_device {scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_HWX25 ; 
 int /*<<< orphan*/  CYCX_X25_CHAN_MTU ; 
 int /*<<< orphan*/  cycx_header_ops ; 
 int /*<<< orphan*/  cycx_netdev_ops ; 

__attribute__((used)) static void cycx_x25_chan_setup(struct net_device *dev)
{
	/* Initialize device driver entry points */
	dev->netdev_ops		= &cycx_netdev_ops;
	dev->header_ops		= &cycx_header_ops;

	/* Initialize media-specific parameters */
	dev->mtu		= CYCX_X25_CHAN_MTU;
	dev->type		= ARPHRD_HWX25;	/* ARP h/w type */
	dev->hard_header_len	= 0;		/* media header length */
	dev->addr_len		= 0;		/* hardware address length */
}