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
struct ovs_key_ipv4 {scalar_t__ ipv4_src; scalar_t__ ipv4_dst; scalar_t__ ipv4_tos; scalar_t__ ipv4_ttl; } ;
struct iphdr {scalar_t__ saddr; scalar_t__ daddr; scalar_t__ tos; scalar_t__ ttl; } ;

/* Variables and functions */
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_change_dsfield (struct iphdr*,int /*<<< orphan*/ ,scalar_t__) ; 
 int make_writable (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  set_ip_addr (struct sk_buff*,struct iphdr*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  set_ip_ttl (struct sk_buff*,struct iphdr*,scalar_t__) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_ipv4(struct sk_buff *skb, const struct ovs_key_ipv4 *ipv4_key)
{
	struct iphdr *nh;
	int err;

	err = make_writable(skb, skb_network_offset(skb) +
				 sizeof(struct iphdr));
	if (unlikely(err))
		return err;

	nh = ip_hdr(skb);

	if (ipv4_key->ipv4_src != nh->saddr)
		set_ip_addr(skb, nh, &nh->saddr, ipv4_key->ipv4_src);

	if (ipv4_key->ipv4_dst != nh->daddr)
		set_ip_addr(skb, nh, &nh->daddr, ipv4_key->ipv4_dst);

	if (ipv4_key->ipv4_tos != nh->tos)
		ipv4_change_dsfield(nh, 0, ipv4_key->ipv4_tos);

	if (ipv4_key->ipv4_ttl != nh->ttl)
		set_ip_ttl(skb, nh, ipv4_key->ipv4_ttl);

	return 0;
}