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
struct phonet_device {int /*<<< orphan*/  addrs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int PN_NO_ADDR ; 
 struct phonet_device* __phonet_get (struct net_device*) ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 struct phonet_device_list* phonet_device_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

u8 phonet_address_get(struct net_device *dev, u8 addr)
{
	struct phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	struct phonet_device *pnd;

	spin_lock_bh(&pndevs->lock);
	pnd = __phonet_get(dev);
	if (pnd) {
		BUG_ON(bitmap_empty(pnd->addrs, 64));

		/* Use same source address as destination, if possible */
		if (!test_bit(addr >> 2, pnd->addrs))
			addr = find_first_bit(pnd->addrs, 64) << 2;
	} else
		addr = PN_NO_ADDR;
	spin_unlock_bh(&pndevs->lock);
	return addr;
}