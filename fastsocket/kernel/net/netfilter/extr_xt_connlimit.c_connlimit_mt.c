#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union nf_inet_addr {int /*<<< orphan*/  ip; int /*<<< orphan*/  ip6; } ;
struct xt_match_param {int* hotdrop; int /*<<< orphan*/  family; struct xt_connlimit_info* matchinfo; } ;
struct xt_connlimit_info {int limit; int inverse; TYPE_2__* data; int /*<<< orphan*/  mask; } ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {TYPE_1__* tuplehash; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; } ;
struct iphdr {int /*<<< orphan*/  saddr; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int count_them (TYPE_2__*,struct nf_conntrack_tuple const*,union nf_inet_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
connlimit_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_connlimit_info *info = par->matchinfo;
	union nf_inet_addr addr;
	struct nf_conntrack_tuple tuple;
	const struct nf_conntrack_tuple *tuple_ptr = &tuple;
	enum ip_conntrack_info ctinfo;
	const struct nf_conn *ct;
	int connections;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct != NULL)
		tuple_ptr = &ct->tuplehash[0].tuple;
	else if (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
				    par->family, &tuple))
		goto hotdrop;

	if (par->family == NFPROTO_IPV6) {
		const struct ipv6hdr *iph = ipv6_hdr(skb);
		memcpy(&addr.ip6, &iph->saddr, sizeof(iph->saddr));
	} else {
		const struct iphdr *iph = ip_hdr(skb);
		addr.ip = iph->saddr;
	}

	spin_lock_bh(&info->data->lock);
	connections = count_them(info->data, tuple_ptr, &addr,
	                         &info->mask, par->family);
	spin_unlock_bh(&info->data->lock);

	if (connections < 0) {
		/* kmalloc failed, drop it entirely */
		*par->hotdrop = true;
		return false;
	}

	return (connections > info->limit) ^ info->inverse;

 hotdrop:
	*par->hotdrop = true;
	return false;
}