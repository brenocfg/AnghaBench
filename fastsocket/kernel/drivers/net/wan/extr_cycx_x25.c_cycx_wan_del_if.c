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
struct wan_device {int dummy; } ;
struct net_device {int dummy; } ;
struct cycx_x25_channel {scalar_t__ state; int /*<<< orphan*/  timer; int /*<<< orphan*/  local_addr; scalar_t__ svc; } ;

/* Variables and functions */
 scalar_t__ WAN_CONNECTED ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct cycx_x25_channel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cycx_wan_del_if(struct wan_device *wandev, struct net_device *dev)
{
	struct cycx_x25_channel *chan = netdev_priv(dev);

	if (chan->svc) {
		kfree(chan->local_addr);
		if (chan->state == WAN_CONNECTED)
			del_timer(&chan->timer);
	}

	return 0;
}