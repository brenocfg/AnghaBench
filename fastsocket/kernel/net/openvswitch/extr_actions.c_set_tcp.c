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
struct tcphdr {scalar_t__ source; scalar_t__ dest; int /*<<< orphan*/  check; } ;
struct sk_buff {int dummy; } ;
struct ovs_key_tcp {scalar_t__ tcp_src; scalar_t__ tcp_dst; } ;

/* Variables and functions */
 int make_writable (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  set_tp_port (struct sk_buff*,scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_tcp(struct sk_buff *skb, const struct ovs_key_tcp *tcp_port_key)
{
	struct tcphdr *th;
	int err;

	err = make_writable(skb, skb_transport_offset(skb) +
				 sizeof(struct tcphdr));
	if (unlikely(err))
		return err;

	th = tcp_hdr(skb);
	if (tcp_port_key->tcp_src != th->source)
		set_tp_port(skb, &th->source, tcp_port_key->tcp_src, &th->check);

	if (tcp_port_key->tcp_dst != th->dest)
		set_tp_port(skb, &th->dest, tcp_port_key->tcp_dst, &th->check);

	return 0;
}