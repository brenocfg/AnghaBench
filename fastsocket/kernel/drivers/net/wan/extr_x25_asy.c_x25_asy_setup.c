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
struct x25_asy {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; struct net_device* dev; int /*<<< orphan*/  magic; } ;
struct net_device {int watchdog_timeo; int tx_queue_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_X25 ; 
 int HZ ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  SLF_INUSE ; 
 int /*<<< orphan*/  SL_MTU ; 
 int /*<<< orphan*/  X25_ASY_MAGIC ; 
 struct x25_asy* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_asy_netdev_ops ; 

__attribute__((used)) static void x25_asy_setup(struct net_device *dev)
{
	struct x25_asy *sl = netdev_priv(dev);

	sl->magic  = X25_ASY_MAGIC;
	sl->dev	   = dev;
	spin_lock_init(&sl->lock);
	set_bit(SLF_INUSE, &sl->flags);

	/*
	 *	Finish setting up the DEVICE info.
	 */

	dev->mtu		= SL_MTU;
	dev->netdev_ops		= &x25_asy_netdev_ops;
	dev->watchdog_timeo	= HZ*20;
	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->type		= ARPHRD_X25;
	dev->tx_queue_len	= 10;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
}