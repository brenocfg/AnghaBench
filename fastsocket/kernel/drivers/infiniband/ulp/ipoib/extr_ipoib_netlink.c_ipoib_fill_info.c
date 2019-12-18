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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  flags; int /*<<< orphan*/  pkey; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_IPOIB_MODE ; 
 int /*<<< orphan*/  IFLA_IPOIB_PKEY ; 
 int /*<<< orphan*/  IFLA_IPOIB_UMCAST ; 
 int /*<<< orphan*/  IPOIB_FLAG_ADMIN_CM ; 
 int /*<<< orphan*/  IPOIB_FLAG_UMCAST ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	u16 val;

	if (nla_put_u16(skb, IFLA_IPOIB_PKEY, priv->pkey))
		goto nla_put_failure;

	val = test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
	if (nla_put_u16(skb, IFLA_IPOIB_MODE, val))
		goto nla_put_failure;

	val = test_bit(IPOIB_FLAG_UMCAST, &priv->flags);
	if (nla_put_u16(skb, IFLA_IPOIB_UMCAST, val))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}