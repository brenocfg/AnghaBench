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
struct net_device {int dummy; } ;
struct neighbour {int dummy; } ;
struct in6_addr {int dummy; } ;
struct icmp6hdr {int /*<<< orphan*/  icmp6_type; } ;

/* Variables and functions */
 int IFA_F_OPTIMISTIC ; 
 int IFA_F_TENTATIVE ; 
 int /*<<< orphan*/  NDISC_NEIGHBOUR_SOLICITATION ; 
 int /*<<< orphan*/  ND_OPT_SOURCE_LL_ADDR ; 
 int /*<<< orphan*/  __ndisc_send (struct net_device*,struct neighbour*,struct in6_addr const*,struct in6_addr const*,struct icmp6hdr*,struct in6_addr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr const*) ; 
 scalar_t__ ipv6_get_lladdr (struct net_device*,struct in6_addr*,int) ; 

void ndisc_send_ns(struct net_device *dev, struct neighbour *neigh,
		   const struct in6_addr *solicit,
		   const struct in6_addr *daddr, const struct in6_addr *saddr)
{
	struct in6_addr addr_buf;
	struct icmp6hdr icmp6h = {
		.icmp6_type = NDISC_NEIGHBOUR_SOLICITATION,
	};

	if (saddr == NULL) {
		if (ipv6_get_lladdr(dev, &addr_buf,
				   (IFA_F_TENTATIVE|IFA_F_OPTIMISTIC)))
			return;
		saddr = &addr_buf;
	}

	__ndisc_send(dev, neigh, daddr, saddr,
		     &icmp6h, solicit,
		     !ipv6_addr_any(saddr) ? ND_OPT_SOURCE_LL_ADDR : 0);
}