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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct in6_addr {int dummy; } ;
struct flowi {int oif; scalar_t__ fl_icmp_code; int /*<<< orphan*/  fl_icmp_type; int /*<<< orphan*/  proto; int /*<<< orphan*/  fl6_dst; int /*<<< orphan*/  fl6_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_sk_classify_flow (struct sock*,struct flowi*) ; 

void icmpv6_flow_init(struct sock *sk, struct flowi *fl,
		      u8 type,
		      const struct in6_addr *saddr,
		      const struct in6_addr *daddr,
		      int oif)
{
	memset(fl, 0, sizeof(*fl));
	ipv6_addr_copy(&fl->fl6_src, saddr);
	ipv6_addr_copy(&fl->fl6_dst, daddr);
	fl->proto	 	= IPPROTO_ICMPV6;
	fl->fl_icmp_type	= type;
	fl->fl_icmp_code	= 0;
	fl->oif			= oif;
	security_sk_classify_flow(sk, fl);
}