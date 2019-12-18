#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ipoib_dev_priv {int pkey; int child_type; TYPE_1__* dev; int /*<<< orphan*/  child_intfs; int /*<<< orphan*/  list; TYPE_1__* parent; int /*<<< orphan*/  port; TYPE_3__* ca; int /*<<< orphan*/  flags; int /*<<< orphan*/  admin_mtu; int /*<<< orphan*/  mcast_mtu; int /*<<< orphan*/  max_ib_mtu; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int* broadcast; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  iflink; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
 int /*<<< orphan*/  IPOIB_FLAG_SUBINTERFACE ; 
 int IPOIB_LEGACY_CHILD ; 
 int /*<<< orphan*/  IPOIB_UD_MTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_parent ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ipoib_add_pkey_attr (TYPE_1__*) ; 
 scalar_t__ ipoib_add_umcast_attr (TYPE_1__*) ; 
 scalar_t__ ipoib_cm_add_mode_attr (TYPE_1__*) ; 
 int /*<<< orphan*/  ipoib_create_debug_files (TYPE_1__*) ; 
 int /*<<< orphan*/  ipoib_delete_debug_files (TYPE_1__*) ; 
 int /*<<< orphan*/  ipoib_dev_cleanup (TYPE_1__*) ; 
 int ipoib_dev_init (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ipoib_set_dev_features (struct ipoib_dev_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdevice (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (TYPE_1__*) ; 

int __ipoib_vlan_add(struct ipoib_dev_priv *ppriv, struct ipoib_dev_priv *priv,
		     u16 pkey, int type)
{
	int result;

	priv->max_ib_mtu = ppriv->max_ib_mtu;
	/* MTU will be reset when mcast join happens */
	priv->dev->mtu   = IPOIB_UD_MTU(priv->max_ib_mtu);
	priv->mcast_mtu  = priv->admin_mtu = priv->dev->mtu;
	set_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags);

	result = ipoib_set_dev_features(priv, ppriv->ca);
	if (result)
		goto err;

	priv->pkey = pkey;

	memcpy(priv->dev->dev_addr, ppriv->dev->dev_addr, INFINIBAND_ALEN);
	priv->dev->broadcast[8] = pkey >> 8;
	priv->dev->broadcast[9] = pkey & 0xff;

	result = ipoib_dev_init(priv->dev, ppriv->ca, ppriv->port);
	if (result < 0) {
		ipoib_warn(ppriv, "failed to initialize subinterface: "
			   "device %s, port %d",
			   ppriv->ca->name, ppriv->port);
		goto err;
	}

	result = register_netdevice(priv->dev);
	if (result) {
		ipoib_warn(priv, "failed to initialize; error %i", result);
		goto register_failed;
	}

	priv->parent = ppriv->dev;

	ipoib_create_debug_files(priv->dev);

	/* RTNL childs don't need proprietary sysfs entries */
	if (type == IPOIB_LEGACY_CHILD) {
		if (ipoib_cm_add_mode_attr(priv->dev))
			goto sysfs_failed;
		if (ipoib_add_pkey_attr(priv->dev))
			goto sysfs_failed;
		if (ipoib_add_umcast_attr(priv->dev))
			goto sysfs_failed;

		if (device_create_file(&priv->dev->dev, &dev_attr_parent))
			goto sysfs_failed;
	}

	priv->child_type  = type;
	priv->dev->iflink = ppriv->dev->ifindex;
	list_add_tail(&priv->list, &ppriv->child_intfs);

	return 0;

sysfs_failed:
	result = -ENOMEM;
	ipoib_delete_debug_files(priv->dev);
	unregister_netdevice(priv->dev);

register_failed:
	ipoib_dev_cleanup(priv->dev);

err:
	return result;
}