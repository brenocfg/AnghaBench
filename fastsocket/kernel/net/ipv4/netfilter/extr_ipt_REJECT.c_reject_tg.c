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
struct xt_target_param {int /*<<< orphan*/  hooknum; struct ipt_reject_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct ipt_reject_info {int with; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_HOST_ANO ; 
 int /*<<< orphan*/  ICMP_HOST_UNREACH ; 
 int /*<<< orphan*/  ICMP_NET_ANO ; 
 int /*<<< orphan*/  ICMP_NET_UNREACH ; 
 int /*<<< orphan*/  ICMP_PKT_FILTERED ; 
 int /*<<< orphan*/  ICMP_PORT_UNREACH ; 
 int /*<<< orphan*/  ICMP_PROT_UNREACH ; 
#define  IPT_ICMP_ADMIN_PROHIBITED 136 
#define  IPT_ICMP_ECHOREPLY 135 
#define  IPT_ICMP_HOST_PROHIBITED 134 
#define  IPT_ICMP_HOST_UNREACHABLE 133 
#define  IPT_ICMP_NET_PROHIBITED 132 
#define  IPT_ICMP_NET_UNREACHABLE 131 
#define  IPT_ICMP_PORT_UNREACHABLE 130 
#define  IPT_ICMP_PROT_UNREACHABLE 129 
#define  IPT_TCP_RESET 128 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  send_reset (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_unreach (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
reject_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct ipt_reject_info *reject = par->targinfo;

	/* WARNING: This code causes reentry within iptables.
	   This means that the iptables jump stack is now crap.  We
	   must return an absolute verdict. --RR */
	switch (reject->with) {
	case IPT_ICMP_NET_UNREACHABLE:
		send_unreach(skb, ICMP_NET_UNREACH);
		break;
	case IPT_ICMP_HOST_UNREACHABLE:
		send_unreach(skb, ICMP_HOST_UNREACH);
		break;
	case IPT_ICMP_PROT_UNREACHABLE:
		send_unreach(skb, ICMP_PROT_UNREACH);
		break;
	case IPT_ICMP_PORT_UNREACHABLE:
		send_unreach(skb, ICMP_PORT_UNREACH);
		break;
	case IPT_ICMP_NET_PROHIBITED:
		send_unreach(skb, ICMP_NET_ANO);
		break;
	case IPT_ICMP_HOST_PROHIBITED:
		send_unreach(skb, ICMP_HOST_ANO);
		break;
	case IPT_ICMP_ADMIN_PROHIBITED:
		send_unreach(skb, ICMP_PKT_FILTERED);
		break;
	case IPT_TCP_RESET:
		send_reset(skb, par->hooknum);
	case IPT_ICMP_ECHOREPLY:
		/* Doesn't happen. */
		break;
	}

	return NF_DROP;
}