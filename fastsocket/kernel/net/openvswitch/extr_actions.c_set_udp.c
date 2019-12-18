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
struct udphdr {scalar_t__ source; scalar_t__ dest; } ;
struct sk_buff {int dummy; } ;
struct ovs_key_udp {scalar_t__ udp_src; scalar_t__ udp_dst; } ;

/* Variables and functions */
 int make_writable (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  set_udp_port (struct sk_buff*,scalar_t__*,scalar_t__) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_udp(struct sk_buff *skb, const struct ovs_key_udp *udp_port_key)
{
	struct udphdr *uh;
	int err;

	err = make_writable(skb, skb_transport_offset(skb) +
				 sizeof(struct udphdr));
	if (unlikely(err))
		return err;

	uh = udp_hdr(skb);
	if (udp_port_key->udp_src != uh->source)
		set_udp_port(skb, &uh->source, udp_port_key->udp_src);

	if (udp_port_key->udp_dst != uh->dest)
		set_udp_port(skb, &uh->dest, udp_port_key->udp_dst);

	return 0;
}