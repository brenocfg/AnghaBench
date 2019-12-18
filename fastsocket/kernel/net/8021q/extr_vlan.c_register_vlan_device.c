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
typedef  scalar_t__ u16 ;
struct vlan_net {int name_type; } ;
struct vlan_dev_info {int dummy; } ;
struct net_device {char* name; int /*<<< orphan*/ * rtnl_link_ops; int /*<<< orphan*/  mtu; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * dent; struct net_device* real_dev; scalar_t__ vlan_id; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ERANGE ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  VLAN_FLAG_REORDER_HDR ; 
#define  VLAN_NAME_TYPE_PLUS_VID 131 
#define  VLAN_NAME_TYPE_PLUS_VID_NO_PAD 130 
#define  VLAN_NAME_TYPE_RAW_PLUS_VID 129 
#define  VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD 128 
 scalar_t__ VLAN_VID_MASK ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct vlan_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int register_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__,...) ; 
 int vlan_check_real_dev (struct net_device*,scalar_t__) ; 
 TYPE_1__* vlan_dev_info (struct net_device*) ; 
 int /*<<< orphan*/  vlan_link_ops ; 
 int /*<<< orphan*/  vlan_net_id ; 
 int /*<<< orphan*/  vlan_setup ; 

__attribute__((used)) static int register_vlan_device(struct net_device *real_dev, u16 vlan_id)
{
	struct net_device *new_dev;
	struct net *net = dev_net(real_dev);
	struct vlan_net *vn = net_generic(net, vlan_net_id);
	char name[IFNAMSIZ];
	int err;

	if (vlan_id >= VLAN_VID_MASK)
		return -ERANGE;

	err = vlan_check_real_dev(real_dev, vlan_id);
	if (err < 0)
		return err;

	/* Gotta set up the fields for the device. */
	switch (vn->name_type) {
	case VLAN_NAME_TYPE_RAW_PLUS_VID:
		/* name will look like:	 eth1.0005 */
		snprintf(name, IFNAMSIZ, "%s.%.4i", real_dev->name, vlan_id);
		break;
	case VLAN_NAME_TYPE_PLUS_VID_NO_PAD:
		/* Put our vlan.VID in the name.
		 * Name will look like:	 vlan5
		 */
		snprintf(name, IFNAMSIZ, "vlan%i", vlan_id);
		break;
	case VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD:
		/* Put our vlan.VID in the name.
		 * Name will look like:	 eth0.5
		 */
		snprintf(name, IFNAMSIZ, "%s.%i", real_dev->name, vlan_id);
		break;
	case VLAN_NAME_TYPE_PLUS_VID:
		/* Put our vlan.VID in the name.
		 * Name will look like:	 vlan0005
		 */
	default:
		snprintf(name, IFNAMSIZ, "vlan%.4i", vlan_id);
	}

	new_dev = alloc_netdev(sizeof(struct vlan_dev_info), name,
				  vlan_setup);

	if (new_dev == NULL)
		return -ENOBUFS;

	dev_net_set(new_dev, net);
	/* need 4 bytes for extra VLAN header info,
	 * hope the underlying device can handle it.
	 */
	new_dev->mtu = real_dev->mtu;

	vlan_dev_info(new_dev)->vlan_id = vlan_id;
	vlan_dev_info(new_dev)->real_dev = real_dev;
	vlan_dev_info(new_dev)->dent = NULL;
	vlan_dev_info(new_dev)->flags = VLAN_FLAG_REORDER_HDR;

	new_dev->rtnl_link_ops = &vlan_link_ops;
	err = register_vlan_dev(new_dev);
	if (err < 0)
		goto out_free_newdev;

	return 0;

out_free_newdev:
	free_netdev(new_dev);
	return err;
}