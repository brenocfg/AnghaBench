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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int AARP_HASH_SIZE ; 
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  __aarp_expire_device (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  aarp_lock ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * proxies ; 
 int /*<<< orphan*/ * resolved ; 
 int /*<<< orphan*/ * unresolved ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aarp_device_event(struct notifier_block *this, unsigned long event,
			     void *ptr)
{
	struct net_device *dev = ptr;
	int ct;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	if (event == NETDEV_DOWN) {
		write_lock_bh(&aarp_lock);

		for (ct = 0; ct < AARP_HASH_SIZE; ct++) {
			__aarp_expire_device(&resolved[ct], dev);
			__aarp_expire_device(&unresolved[ct], dev);
			__aarp_expire_device(&proxies[ct], dev);
		}

		write_unlock_bh(&aarp_lock);
	}
	return NOTIFY_DONE;
}