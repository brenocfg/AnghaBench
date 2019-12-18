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
typedef  int u64 ;
struct sk_buff {int dummy; } ;
struct iphdr {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int LRO_IPV4 ; 
 int LRO_TCP ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 unsigned int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,unsigned int) ; 
 void* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static int nes_lro_get_skb_hdr(struct sk_buff *skb, void **iphdr,
			       void **tcph, u64 *hdr_flags, void *priv)
{
	unsigned int ip_len;
	struct iphdr *iph;
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	if (iph->protocol != IPPROTO_TCP)
		return -1;
	ip_len = ip_hdrlen(skb);
	skb_set_transport_header(skb, ip_len);
	*tcph = tcp_hdr(skb);

	*hdr_flags = LRO_IPV4 | LRO_TCP;
	*iphdr = iph;
	return 0;
}