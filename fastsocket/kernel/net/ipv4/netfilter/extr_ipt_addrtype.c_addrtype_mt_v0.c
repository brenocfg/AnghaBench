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
struct xt_match_param {struct ipt_addrtype_info* matchinfo; scalar_t__ out; scalar_t__ in; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct ipt_addrtype_info {int invert_source; int invert_dest; scalar_t__ dest; scalar_t__ source; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 struct net* dev_net (scalar_t__) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 int match_type (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
addrtype_mt_v0(const struct sk_buff *skb, const struct xt_match_param *par)
{
	struct net *net = dev_net(par->in ? par->in : par->out);
	const struct ipt_addrtype_info *info = par->matchinfo;
	const struct iphdr *iph = ip_hdr(skb);
	bool ret = true;

	if (info->source)
		ret &= match_type(net, NULL, iph->saddr, info->source) ^
		       info->invert_source;
	if (info->dest)
		ret &= match_type(net, NULL, iph->daddr, info->dest) ^
		       info->invert_dest;

	return ret;
}