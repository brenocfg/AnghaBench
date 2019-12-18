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
struct vport {int dummy; } ;
struct ovs_net {int /*<<< orphan*/  dp_notify_work; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned long NETDEV_UNREGISTER ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct ovs_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_is_internal_dev (struct net_device*) ; 
 int /*<<< orphan*/  ovs_net_id ; 
 struct vport* ovs_netdev_get_vport (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dp_device_event(struct notifier_block *unused, unsigned long event,
			   void *ptr)
{
	struct ovs_net *ovs_net;
	struct net_device *dev = ptr;
	struct vport *vport = NULL;

	if (!ovs_is_internal_dev(dev))
		vport = ovs_netdev_get_vport(dev);

	if (!vport)
		return NOTIFY_DONE;

	if (event == NETDEV_UNREGISTER) {
		ovs_net = net_generic(dev_net(dev), ovs_net_id);
		schedule_work(&ovs_net->dp_notify_work);
	}

	return NOTIFY_DONE;
}