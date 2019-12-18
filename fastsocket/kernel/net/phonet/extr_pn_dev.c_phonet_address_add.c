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
 int EEXIST ; 
 int ENOMEM ; 
 struct phonet_device* __phonet_device_alloc (struct net_device*) ; 
 struct phonet_device* __phonet_get (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct phonet_device_list* phonet_device_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int phonet_address_add(struct net_device *dev, u8 addr)
{
	struct phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	struct phonet_device *pnd;
	int err = 0;

	spin_lock_bh(&pndevs->lock);
	/* Find or create Phonet-specific device data */
	pnd = __phonet_get(dev);
	if (pnd == NULL)
		pnd = __phonet_device_alloc(dev);
	if (unlikely(pnd == NULL))
		err = -ENOMEM;
	else if (test_and_set_bit(addr >> 2, pnd->addrs))
		err = -EEXIST;
	spin_unlock_bh(&pndevs->lock);
	return err;
}