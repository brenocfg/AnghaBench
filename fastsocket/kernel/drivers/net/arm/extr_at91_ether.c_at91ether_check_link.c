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
struct at91_private {int /*<<< orphan*/  check_timer; } ;

/* Variables and functions */
 scalar_t__ LINK_POLL_INTERVAL ; 
 int /*<<< orphan*/  disable_mdi () ; 
 int /*<<< orphan*/  enable_mdi () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct at91_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  update_linkspeed (struct net_device*,int) ; 

__attribute__((used)) static void at91ether_check_link(unsigned long dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct at91_private *lp = netdev_priv(dev);

	enable_mdi();
	update_linkspeed(dev, 1);
	disable_mdi();

	mod_timer(&lp->check_timer, jiffies + LINK_POLL_INTERVAL);
}