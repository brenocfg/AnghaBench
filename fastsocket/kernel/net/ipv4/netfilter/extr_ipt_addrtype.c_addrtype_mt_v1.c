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
struct xt_match_param {struct net_device* out; struct net_device* in; struct ipt_addrtype_info_v1* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipt_addrtype_info_v1 {int flags; scalar_t__ dest; scalar_t__ source; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int IPT_ADDRTYPE_INVERT_DEST ; 
 int IPT_ADDRTYPE_INVERT_SOURCE ; 
 int IPT_ADDRTYPE_LIMIT_IFACE_IN ; 
 int IPT_ADDRTYPE_LIMIT_IFACE_OUT ; 
 struct net* dev_net (struct net_device*) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 int match_type (struct net*,struct net_device const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
addrtype_mt_v1(const struct sk_buff *skb, const struct xt_match_param *par)
{
	struct net *net = dev_net(par->in ? par->in : par->out);
	const struct ipt_addrtype_info_v1 *info = par->matchinfo;
	const struct iphdr *iph = ip_hdr(skb);
	const struct net_device *dev = NULL;
	bool ret = true;

	if (info->flags & IPT_ADDRTYPE_LIMIT_IFACE_IN)
		dev = par->in;
	else if (info->flags & IPT_ADDRTYPE_LIMIT_IFACE_OUT)
		dev = par->out;

	if (info->source)
		ret &= match_type(net, dev, iph->saddr, info->source) ^
		       (info->flags & IPT_ADDRTYPE_INVERT_SOURCE);
	if (ret && info->dest)
		ret &= match_type(net, dev, iph->daddr, info->dest) ^
		       !!(info->flags & IPT_ADDRTYPE_INVERT_DEST);
	return ret;
}