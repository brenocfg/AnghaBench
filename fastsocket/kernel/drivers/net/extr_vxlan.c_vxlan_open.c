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
struct vxlan_sock {int dummy; } ;
struct vxlan_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_ip; } ;
struct vxlan_dev {int /*<<< orphan*/  age_timer; scalar_t__ age_interval; int /*<<< orphan*/  igmp_join; TYPE_1__ default_dst; struct vxlan_sock* vn_sock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOTCONN ; 
 scalar_t__ FDB_AGE_INTERVAL ; 
 scalar_t__ IN_MULTICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct vxlan_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vxlan_group_used (struct vxlan_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_net_id ; 
 int /*<<< orphan*/  vxlan_sock_hold (struct vxlan_sock*) ; 
 int /*<<< orphan*/  vxlan_wq ; 

__attribute__((used)) static int vxlan_open(struct net_device *dev)
{
	struct vxlan_net *vn = net_generic(dev_net(dev), vxlan_net_id);
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_sock *vs = vxlan->vn_sock;

	/* socket hasn't been created */
	if (!vs)
		return -ENOTCONN;

	if (IN_MULTICAST(ntohl(vxlan->default_dst.remote_ip)) &&
	    vxlan_group_used(vn, vxlan->default_dst.remote_ip)) {
		vxlan_sock_hold(vs);
		dev_hold(dev);
		queue_work(vxlan_wq, &vxlan->igmp_join);
	}

	if (vxlan->age_interval)
		mod_timer(&vxlan->age_timer, jiffies + FDB_AGE_INTERVAL);

	return 0;
}