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
struct uwb_dev_addr {int dummy; } ;
struct uwb_dev {int /*<<< orphan*/  dev_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct uwb_dev* to_uwb_dev (struct device*) ; 
 int /*<<< orphan*/  uwb_dev_addr_cmp (struct uwb_dev_addr*,int /*<<< orphan*/ *) ; 

int __uwb_dev_addr_assigned_check(struct device *dev, void *_addr)
{
	struct uwb_dev *uwb_dev = to_uwb_dev(dev);
	struct uwb_dev_addr *addr = _addr;
	if (!uwb_dev_addr_cmp(addr, &uwb_dev->dev_addr))
		return !0;
	return 0;
}