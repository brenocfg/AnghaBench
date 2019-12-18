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
struct hash_ip6_elem {int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 int /*<<< orphan*/  NLA_PUT_IPADDR6 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
hash_ip6_data_list(struct sk_buff *skb, const struct hash_ip6_elem *data)
{
	NLA_PUT_IPADDR6(skb, IPSET_ATTR_IP, &data->ip);
	return 0;

nla_put_failure:
	return 1;
}