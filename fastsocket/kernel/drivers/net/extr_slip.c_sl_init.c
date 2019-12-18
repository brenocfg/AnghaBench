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
struct slip {scalar_t__ mode; int /*<<< orphan*/  mtu; } ;
struct net_device {int watchdog_timeo; scalar_t__ type; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_SLIP ; 
 int HZ ; 
 struct slip* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int sl_init(struct net_device *dev)
{
	struct slip *sl = netdev_priv(dev);

	/*
	 *	Finish setting up the DEVICE info.
	 */

	dev->mtu		= sl->mtu;
	dev->type		= ARPHRD_SLIP + sl->mode;
#ifdef SL_CHECK_TRANSMIT
	dev->watchdog_timeo	= 20*HZ;
#endif
	return 0;
}