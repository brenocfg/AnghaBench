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
struct vport {struct datapath* dp; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_base_lock ; 
 struct vport* ovs_internal_dev_get_vport (struct net_device*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct datapath *get_dp(struct net *net, int dp_ifindex)
{
	struct datapath *dp = NULL;
	struct net_device *dev;

	read_lock(&dev_base_lock);
	dev = __dev_get_by_index(net, dp_ifindex);
	if (dev) {
		struct vport *vport = ovs_internal_dev_get_vport(dev);
		if (vport)
			dp = vport->dp;
	}
	read_unlock(&dev_base_lock);

	return dp;
}