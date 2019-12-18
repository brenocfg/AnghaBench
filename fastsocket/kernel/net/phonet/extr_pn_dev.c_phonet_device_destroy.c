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
typedef  int u8 ;
struct phonet_device_list {int /*<<< orphan*/  lock; } ;
struct phonet_device {int /*<<< orphan*/  addrs; int /*<<< orphan*/  list; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  RTM_DELADDR ; 
 struct phonet_device* __phonet_get (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (struct phonet_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phonet_address_notify (int /*<<< orphan*/ ,struct net_device*,int) ; 
 struct phonet_device_list* phonet_device_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void phonet_device_destroy(struct net_device *dev)
{
	struct phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	struct phonet_device *pnd;

	ASSERT_RTNL();

	spin_lock_bh(&pndevs->lock);
	pnd = __phonet_get(dev);
	if (pnd)
		list_del(&pnd->list);
	spin_unlock_bh(&pndevs->lock);

	if (pnd) {
		u8 addr;

		for (addr = find_first_bit(pnd->addrs, 64); addr < 64;
			addr = find_next_bit(pnd->addrs, 64, 1+addr))
			phonet_address_notify(RTM_DELADDR, dev, addr);
		kfree(pnd);
	}
}