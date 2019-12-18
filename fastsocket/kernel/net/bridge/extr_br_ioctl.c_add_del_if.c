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
struct net_bridge {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int br_add_if (struct net_bridge*,struct net_device*) ; 
 int br_del_if (struct net_bridge*,struct net_device*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 

__attribute__((used)) static int add_del_if(struct net_bridge *br, int ifindex, int isadd)
{
	struct net_device *dev;
	int ret;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	dev = dev_get_by_index(dev_net(br->dev), ifindex);
	if (dev == NULL)
		return -EINVAL;

	if (isadd)
		ret = br_add_if(br, dev);
	else
		ret = br_del_if(br, dev);

	dev_put(dev);
	return ret;
}