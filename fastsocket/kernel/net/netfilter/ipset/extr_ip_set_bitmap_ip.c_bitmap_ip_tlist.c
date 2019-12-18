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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {size_t* args; } ;
struct ip_set {struct bitmap_ip* data; } ;
struct bitmap_ip {unsigned long* members; scalar_t__ elements; size_t hosts; scalar_t__ first_ip; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IPSET_ATTR_ADT ; 
 int /*<<< orphan*/  IPSET_ATTR_DATA ; 
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 int /*<<< orphan*/  IPSET_ATTR_TIMEOUT ; 
 int /*<<< orphan*/  NLA_PUT_IPADDR4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_NET32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ ip_set_timeout_get (unsigned long const) ; 
 int /*<<< orphan*/  ip_set_timeout_test (unsigned long const) ; 
 int /*<<< orphan*/  ipset_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* ipset_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
bitmap_ip_tlist(const struct ip_set *set,
		struct sk_buff *skb, struct netlink_callback *cb)
{
	const struct bitmap_ip *map = set->data;
	struct nlattr *adt, *nested;
	u32 id, first = cb->args[2];
	const unsigned long *members = map->members;

	adt = ipset_nest_start(skb, IPSET_ATTR_ADT);
	if (!adt)
		return -EMSGSIZE;
	for (; cb->args[2] < map->elements; cb->args[2]++) {
		id = cb->args[2];
		if (!ip_set_timeout_test(members[id]))
			continue;
		nested = ipset_nest_start(skb, IPSET_ATTR_DATA);
		if (!nested) {
			if (id == first) {
				nla_nest_cancel(skb, adt);
				return -EMSGSIZE;
			} else
				goto nla_put_failure;
		}
		NLA_PUT_IPADDR4(skb, IPSET_ATTR_IP,
				htonl(map->first_ip + id * map->hosts));
		NLA_PUT_NET32(skb, IPSET_ATTR_TIMEOUT,
			      htonl(ip_set_timeout_get(members[id])));
		ipset_nest_end(skb, nested);
	}
	ipset_nest_end(skb, adt);

	/* Set listing finished */
	cb->args[2] = 0;

	return 0;

nla_put_failure:
	nla_nest_cancel(skb, nested);
	ipset_nest_end(skb, adt);
	if (unlikely(id == first)) {
		cb->args[2] = 0;
		return -EMSGSIZE;
	}
	return 0;
}