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
struct net_device {int /*<<< orphan*/  addr_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_for_each_tx_queue (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rose_netdev_addr_lock_key ; 
 int /*<<< orphan*/  rose_set_lockdep_one ; 

__attribute__((used)) static void rose_set_lockdep_key(struct net_device *dev)
{
	lockdep_set_class(&dev->addr_list_lock, &rose_netdev_addr_lock_key);
	netdev_for_each_tx_queue(dev, rose_set_lockdep_one, NULL);
}