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
struct cycx_x25_channel {int idle_tmout; int /*<<< orphan*/  timer; scalar_t__ svc; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct cycx_x25_channel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void reset_timer(struct net_device *dev)
{
	struct cycx_x25_channel *chan = netdev_priv(dev);

	if (chan->svc)
		mod_timer(&chan->timer, jiffies+chan->idle_tmout*HZ);
}