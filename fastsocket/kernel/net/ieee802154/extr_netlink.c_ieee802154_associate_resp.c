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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee802154_addr {int /*<<< orphan*/  pan_id; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  addr_type; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct TYPE_2__ {int (* assoc_resp ) (struct net_device*,struct ieee802154_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_pan_id ) (struct net_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IEEE802154_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE802154_ADDR_LONG ; 
 size_t IEEE802154_ATTR_DEST_HW_ADDR ; 
 size_t IEEE802154_ATTR_DEST_SHORT_ADDR ; 
 size_t IEEE802154_ATTR_STATUS ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 TYPE_1__* ieee802154_mlme_ops (struct net_device*) ; 
 struct net_device* ieee802154_nl_get_dev (struct genl_info*) ; 
 int /*<<< orphan*/  nla_get_u16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int stub2 (struct net_device*,struct ieee802154_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee802154_associate_resp(struct sk_buff *skb,
		struct genl_info *info)
{
	struct net_device *dev;
	struct ieee802154_addr addr;
	int ret = -EINVAL;

	if (!info->attrs[IEEE802154_ATTR_STATUS] ||
	    !info->attrs[IEEE802154_ATTR_DEST_HW_ADDR] ||
	    !info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR])
		return -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	if (!dev)
		return -ENODEV;

	addr.addr_type = IEEE802154_ADDR_LONG;
	nla_memcpy(addr.hwaddr, info->attrs[IEEE802154_ATTR_DEST_HW_ADDR],
			IEEE802154_ADDR_LEN);
	addr.pan_id = ieee802154_mlme_ops(dev)->get_pan_id(dev);


	ret = ieee802154_mlme_ops(dev)->assoc_resp(dev, &addr,
		nla_get_u16(info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR]),
		nla_get_u8(info->attrs[IEEE802154_ATTR_STATUS]));

	dev_put(dev);
	return ret;
}