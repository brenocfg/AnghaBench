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
struct tnl_ptk_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct gre_cisco_protocol {int (* handler ) (struct sk_buff*,struct tnl_ptk_info*) ;} ;

/* Variables and functions */
 int GRE_IP_PROTO_MAX ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_PORT_UNREACH ; 
 int PACKET_RCVD ; 
 int /*<<< orphan*/ * gre_cisco_proto_list ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ parse_gre_header (struct sk_buff*,struct tnl_ptk_info*,int*) ; 
 struct gre_cisco_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct sk_buff*,struct tnl_ptk_info*) ; 

__attribute__((used)) static int gre_cisco_rcv(struct sk_buff *skb)
{
	struct tnl_ptk_info tpi;
	int i;
	bool csum_err = false;

	if (parse_gre_header(skb, &tpi, &csum_err) < 0)
		goto drop;

	rcu_read_lock();
	for (i = 0; i < GRE_IP_PROTO_MAX; i++) {
		struct gre_cisco_protocol *proto;
		int ret;

		proto = rcu_dereference(gre_cisco_proto_list[i]);
		if (!proto)
			continue;
		ret = proto->handler(skb, &tpi);
		if (ret == PACKET_RCVD) {
			rcu_read_unlock();
			return 0;
		}
	}
	rcu_read_unlock();

	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);
drop:
	kfree_skb(skb);
	return 0;
}