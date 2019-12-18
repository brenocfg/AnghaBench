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
typedef  int /*<<< orphan*/  u32 ;
struct tnl_ptk_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct gre_cisco_protocol {scalar_t__ (* err_handler ) (struct sk_buff*,int /*<<< orphan*/ ,struct tnl_ptk_info*) ;} ;

/* Variables and functions */
 int GRE_IP_PROTO_MAX ; 
 scalar_t__ PACKET_RCVD ; 
 int /*<<< orphan*/ * gre_cisco_proto_list ; 
 scalar_t__ parse_gre_header (struct sk_buff*,struct tnl_ptk_info*,int*) ; 
 struct gre_cisco_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ stub1 (struct sk_buff*,int /*<<< orphan*/ ,struct tnl_ptk_info*) ; 

__attribute__((used)) static void gre_cisco_err(struct sk_buff *skb, u32 info)
{
	/* All the routers (except for Linux) return only
	 * 8 bytes of packet payload. It means, that precise relaying of
	 * ICMP in the real Internet is absolutely infeasible.
	 *
	 * Moreover, Cisco "wise men" put GRE key to the third word
	 * in GRE header. It makes impossible maintaining even soft
	 * state for keyed
	 * GRE tunnels with enabled checksum. Tell them "thank you".
	 *
	 * Well, I wonder, rfc1812 was written by Cisco employee,
	 * what the hell these idiots break standards established
	 * by themselves???
	 */

	struct tnl_ptk_info tpi;
	bool csum_err = false;
	int i;

	if (parse_gre_header(skb, &tpi, &csum_err)) {
		if (!csum_err)		/* ignore csum errors. */
			return;
	}

	rcu_read_lock();
	for (i = 0; i < GRE_IP_PROTO_MAX; i++) {
		struct gre_cisco_protocol *proto;

		proto = rcu_dereference(gre_cisco_proto_list[i]);
		if (!proto)
			continue;

		if (proto->err_handler(skb, info, &tpi) == PACKET_RCVD)
			goto out;

	}
out:
	rcu_read_unlock();
}