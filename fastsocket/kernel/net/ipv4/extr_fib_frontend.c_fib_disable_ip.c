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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arp_ifdown (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ fib_sync_down_dev (struct net_device*,int) ; 
 int /*<<< orphan*/  rt_cache_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fib_disable_ip(struct net_device *dev, int force)
{
	if (fib_sync_down_dev(dev, force))
		fib_flush(dev_net(dev));
	rt_cache_flush(dev_net(dev), 0);
	arp_ifdown(dev);
}