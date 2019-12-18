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
struct vxlan_sock {int dummy; } ;
struct vxlan_dev {int /*<<< orphan*/  stats; struct vxlan_sock* vn_sock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vxlan_fdb_delete_default (struct vxlan_dev*) ; 
 int /*<<< orphan*/  vxlan_sock_release (struct vxlan_sock*) ; 

__attribute__((used)) static void vxlan_uninit(struct net_device *dev)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_sock *vs = vxlan->vn_sock;

	vxlan_fdb_delete_default(vxlan);

	if (vs)
		vxlan_sock_release(vs);
	free_percpu(vxlan->stats);
}