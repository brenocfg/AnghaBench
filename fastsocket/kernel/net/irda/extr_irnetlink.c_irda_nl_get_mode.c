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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; scalar_t__ atalk_ptr; } ;
struct irlap_cb {int /*<<< orphan*/  mode; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRDA_NL_ATTR_IFNAME ; 
 int /*<<< orphan*/  IRDA_NL_ATTR_MODE ; 
 int /*<<< orphan*/  IRDA_NL_CMD_GET_MODE ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 struct net_device* ifname_to_netdev (int /*<<< orphan*/ *,struct genl_info*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  irda_nl_family ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int irda_nl_get_mode(struct sk_buff *skb, struct genl_info *info)
{
	struct net_device * dev;
	struct irlap_cb * irlap;
	struct sk_buff *msg;
	void *hdr;
	int ret = -ENOBUFS;

	dev = ifname_to_netdev(&init_net, info);
	if (!dev)
		return -ENODEV;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		dev_put(dev);
		return -ENOMEM;
	}

	irlap = (struct irlap_cb *)dev->atalk_ptr;
	if (!irlap) {
		ret = -ENODEV;
		goto err_out;
	}

	hdr = genlmsg_put(msg, info->snd_pid, info->snd_seq,
			  &irda_nl_family, 0,  IRDA_NL_CMD_GET_MODE);
	if (hdr == NULL) {
		ret = -EMSGSIZE;
		goto err_out;
	}

	if(nla_put_string(msg, IRDA_NL_ATTR_IFNAME,
			  dev->name))
		goto err_out;

	if(nla_put_u32(msg, IRDA_NL_ATTR_MODE, irlap->mode))
		goto err_out;

	genlmsg_end(msg, hdr);

	return genlmsg_reply(msg, info);

 err_out:
	nlmsg_free(msg);
	dev_put(dev);

	return ret;
}