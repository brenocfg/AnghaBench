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
struct w90p910_ether {int /*<<< orphan*/  check_timer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  update_linkspeed (struct net_device*) ; 

__attribute__((used)) static void w90p910_check_link(unsigned long dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct w90p910_ether *ether = netdev_priv(dev);

	update_linkspeed(dev);
	mod_timer(&ether->check_timer, jiffies + msecs_to_jiffies(1000));
}