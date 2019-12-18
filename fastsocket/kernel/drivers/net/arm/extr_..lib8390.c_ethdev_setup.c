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
struct ei_device {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int ei_debug ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static void ethdev_setup(struct net_device *dev)
{
	struct ei_device *ei_local = (struct ei_device *) netdev_priv(dev);
	if (ei_debug > 1)
		printk(version);

	ether_setup(dev);

	spin_lock_init(&ei_local->page_lock);
}