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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {scalar_t__* args; } ;
struct ipmac_telem {scalar_t__ match; scalar_t__ timeout; int /*<<< orphan*/  ether; } ;
struct ip_set {struct bitmap_ipmac* data; } ;
struct bitmap_ipmac {scalar_t__ last_ip; scalar_t__ first_ip; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPSET_ATTR_ADT ; 
 int /*<<< orphan*/  IPSET_ATTR_DATA ; 
 int /*<<< orphan*/  IPSET_ATTR_ETHER ; 
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 int /*<<< orphan*/  IPSET_ATTR_TIMEOUT ; 
 scalar_t__ MAC_FILLED ; 
 scalar_t__ MAC_UNSET ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_IPADDR4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_NET32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipmac_telem* bitmap_ipmac_elem (struct bitmap_ipmac const*,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_ipmac_exist (struct ipmac_telem const*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ ip_set_timeout_get (scalar_t__) ; 
 int /*<<< orphan*/  ipset_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* ipset_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 

__attribute__((used)) static int
bitmap_ipmac_tlist(const struct ip_set *set,
		   struct sk_buff *skb, struct netlink_callback *cb)
{
	const struct bitmap_ipmac *map = set->data;
	const struct ipmac_telem *elem;
	struct nlattr *atd, *nested;
	u32 id, first = cb->args[2];
	u32 timeout, last = map->last_ip - map->first_ip;

	atd = ipset_nest_start(skb, IPSET_ATTR_ADT);
	if (!atd)
		return -EMSGSIZE;
	for (; cb->args[2] <= last; cb->args[2]++) {
		id = cb->args[2];
		elem = bitmap_ipmac_elem(map, id);
		if (!bitmap_ipmac_exist(elem))
			continue;
		nested = ipset_nest_start(skb, IPSET_ATTR_DATA);
		if (!nested) {
			if (id == first) {
				nla_nest_cancel(skb, atd);
				return -EMSGSIZE;
			} else
				goto nla_put_failure;
		}
		NLA_PUT_IPADDR4(skb, IPSET_ATTR_IP,
				htonl(map->first_ip + id));
		if (elem->match == MAC_FILLED)
			NLA_PUT(skb, IPSET_ATTR_ETHER, ETH_ALEN,
				elem->ether);
		timeout = elem->match == MAC_UNSET ? elem->timeout
				: ip_set_timeout_get(elem->timeout);
		NLA_PUT_NET32(skb, IPSET_ATTR_TIMEOUT, htonl(timeout));
		ipset_nest_end(skb, nested);
	}
	ipset_nest_end(skb, atd);
	/* Set listing finished */
	cb->args[2] = 0;

	return 0;

nla_put_failure:
	nla_nest_cancel(skb, nested);
	ipset_nest_end(skb, atd);
	return -EMSGSIZE;
}