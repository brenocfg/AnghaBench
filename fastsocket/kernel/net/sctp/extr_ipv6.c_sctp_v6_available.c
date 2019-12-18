#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
union sctp_addr {TYPE_1__ v6; } ;
struct sctp_sock {int /*<<< orphan*/  v4mapped; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {int (* available ) (union sctp_addr*,struct sctp_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_UNICAST ; 
 int /*<<< orphan*/  init_net ; 
 int ipv6_addr_type (struct in6_addr*) ; 
 int ipv6_chk_addr (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_only_sock (int /*<<< orphan*/ ) ; 
 TYPE_2__* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_opt2sk (struct sctp_sock*) ; 
 int /*<<< orphan*/  sctp_v6_map_v4 (union sctp_addr*) ; 
 int stub1 (union sctp_addr*,struct sctp_sock*) ; 

__attribute__((used)) static int sctp_v6_available(union sctp_addr *addr, struct sctp_sock *sp)
{
	int type;
	struct in6_addr *in6 = (struct in6_addr *)&addr->v6.sin6_addr;

	type = ipv6_addr_type(in6);
	if (IPV6_ADDR_ANY == type)
		return 1;
	if (type == IPV6_ADDR_MAPPED) {
		if (sp && !sp->v4mapped)
			return 0;
		if (sp && ipv6_only_sock(sctp_opt2sk(sp)))
			return 0;
		sctp_v6_map_v4(addr);
		return sctp_get_af_specific(AF_INET)->available(addr, sp);
	}
	if (!(type & IPV6_ADDR_UNICAST))
		return 0;

	return ipv6_chk_addr(&init_net, in6, NULL, 0);
}