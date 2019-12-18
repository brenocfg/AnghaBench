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
typedef  int u16 ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int pkey; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t IFLA_IPOIB_PKEY ; 
 size_t IFLA_LINK ; 
 int /*<<< orphan*/  IPOIB_FLAG_SUBINTERFACE ; 
 int /*<<< orphan*/  IPOIB_RTNL_CHILD ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __ipoib_vlan_add (struct ipoib_dev_priv*,struct ipoib_dev_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int ipoib_changelink (struct net_device*,struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int nla_get_u16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_new_child_link(struct net_device *dev,
			       struct nlattr *tb[], struct nlattr *data[])
{
	struct net_device *pdev;
	struct ipoib_dev_priv *ppriv;
	u16 child_pkey;
	int err;

	if (!tb[IFLA_LINK])
		return -EINVAL;

	pdev = __dev_get_by_index(&init_net, nla_get_u32(tb[IFLA_LINK]));
	if (!pdev)
		return -ENODEV;

	ppriv = netdev_priv(pdev);

	if (test_bit(IPOIB_FLAG_SUBINTERFACE, &ppriv->flags)) {
		ipoib_warn(ppriv, "child creation disallowed for child devices\n");
		return -EINVAL;
	}

	if (!data || !data[IFLA_IPOIB_PKEY]) {
		ipoib_dbg(ppriv, "no pkey specified, using parent pkey\n");
		child_pkey  = ppriv->pkey;
	} else
		child_pkey  = nla_get_u16(data[IFLA_IPOIB_PKEY]);

	if (child_pkey == 0 || child_pkey == 0x8000)
		return -EINVAL;

	/*
	 * Set the full membership bit, so that we join the right
	 * broadcast group, etc.
	 */
	child_pkey |= 0x8000;

	err = __ipoib_vlan_add(ppriv, netdev_priv(dev), child_pkey, IPOIB_RTNL_CHILD);

	if (!err && data)
		err = ipoib_changelink(dev, tb, data);
	return err;
}