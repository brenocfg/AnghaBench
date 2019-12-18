#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {TYPE_1__* ethtool_ops; } ;
struct TYPE_2__ {int (* set_tso ) (struct net_device*,int /*<<< orphan*/ ) ;int (* set_ufo ) (struct net_device*,int /*<<< orphan*/ ) ;int (* set_sg ) (struct net_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct net_device*,int /*<<< orphan*/ ) ; 
 int stub2 (struct net_device*,int /*<<< orphan*/ ) ; 
 int stub3 (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ethtool_set_sg(struct net_device *dev, u32 data)
{
	int err;

	if (!data && dev->ethtool_ops->set_tso) {
		err = dev->ethtool_ops->set_tso(dev, 0);
		if (err)
			return err;
	}

	if (!data && dev->ethtool_ops->set_ufo) {
		err = dev->ethtool_ops->set_ufo(dev, 0);
		if (err)
			return err;
	}
	return dev->ethtool_ops->set_sg(dev, data);
}