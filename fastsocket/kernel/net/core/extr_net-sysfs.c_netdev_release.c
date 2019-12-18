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
struct net_device_extended_frozen {int dummy; } ;
struct net_device {scalar_t__ reg_state; char* ifalias; int padded; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NETREG_RELEASED ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct net_device_extended_frozen* netdev_extended_frozen (struct net_device*) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static void netdev_release(struct device *d)
{
	struct net_device *dev = to_net_dev(d);
	struct net_device_extended_frozen *dev_ext_frozen;

	BUG_ON(dev->reg_state != NETREG_RELEASED);

	kfree(dev->ifalias);
	dev_ext_frozen = netdev_extended_frozen(dev);
	kfree((char *)dev_ext_frozen - dev->padded);
}