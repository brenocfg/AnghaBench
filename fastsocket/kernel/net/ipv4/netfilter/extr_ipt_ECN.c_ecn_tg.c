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
struct xt_target_param {struct ipt_ECN_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct ipt_ECN_info {int operation; } ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int IPT_ECN_OP_SET_CWR ; 
 int IPT_ECN_OP_SET_ECE ; 
 int IPT_ECN_OP_SET_IP ; 
 unsigned int NF_DROP ; 
 unsigned int XT_CONTINUE ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  set_ect_ip (struct sk_buff*,struct ipt_ECN_info const*) ; 
 int /*<<< orphan*/  set_ect_tcp (struct sk_buff*,struct ipt_ECN_info const*) ; 

__attribute__((used)) static unsigned int
ecn_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct ipt_ECN_info *einfo = par->targinfo;

	if (einfo->operation & IPT_ECN_OP_SET_IP)
		if (!set_ect_ip(skb, einfo))
			return NF_DROP;

	if (einfo->operation & (IPT_ECN_OP_SET_ECE | IPT_ECN_OP_SET_CWR)
	    && ip_hdr(skb)->protocol == IPPROTO_TCP)
		if (!set_ect_tcp(skb, einfo))
			return NF_DROP;

	return XT_CONTINUE;
}