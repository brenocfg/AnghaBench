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
struct vxlan_rdst {int /*<<< orphan*/  list; int /*<<< orphan*/  remote_vni; int /*<<< orphan*/  remote_ip; } ;
struct vxlan_fdb {int /*<<< orphan*/  remotes; int /*<<< orphan*/  state; } ;
struct vxlan_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUD_STALE ; 
 int /*<<< orphan*/  RTM_GETNEIGH ; 
 int /*<<< orphan*/  VXLAN_N_VID ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vxlan_fdb_notify (struct vxlan_dev*,struct vxlan_fdb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxlan_ip_miss(struct net_device *dev, __be32 ipa)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_fdb f = {
		.state = NUD_STALE,
	};
	struct vxlan_rdst remote = {
		.remote_ip = ipa, /* goes to NDA_DST */
		.remote_vni = VXLAN_N_VID,
	};

	INIT_LIST_HEAD(&f.remotes);
	list_add_rcu(&remote.list, &f.remotes);

	vxlan_fdb_notify(vxlan, &f, RTM_GETNEIGH);
}