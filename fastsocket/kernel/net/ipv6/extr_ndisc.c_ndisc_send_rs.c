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
struct net_device {int addr_len; } ;
struct inet6_ifaddr {int flags; } ;
struct in6_addr {int dummy; } ;
struct icmp6hdr {int /*<<< orphan*/  icmp6_type; } ;

/* Variables and functions */
 int IFA_F_OPTIMISTIC ; 
 int /*<<< orphan*/  NDISC_ROUTER_SOLICITATION ; 
 int /*<<< orphan*/  ND_OPT_SOURCE_LL_ADDR ; 
 int /*<<< orphan*/  __ndisc_send (struct net_device*,int /*<<< orphan*/ *,struct in6_addr const*,struct in6_addr const*,struct icmp6hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr* ipv6_get_ifaddr (int /*<<< orphan*/ ,struct in6_addr const*,struct net_device*,int) ; 

void ndisc_send_rs(struct net_device *dev, const struct in6_addr *saddr,
		   const struct in6_addr *daddr)
{
	struct icmp6hdr icmp6h = {
		.icmp6_type = NDISC_ROUTER_SOLICITATION,
	};
	int send_sllao = dev->addr_len;

#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	/*
	 * According to section 2.2 of RFC 4429, we must not
	 * send router solicitations with a sllao from
	 * optimistic addresses, but we may send the solicitation
	 * if we don't include the sllao.  So here we check
	 * if our address is optimistic, and if so, we
	 * suppress the inclusion of the sllao.
	 */
	if (send_sllao) {
		struct inet6_ifaddr *ifp = ipv6_get_ifaddr(dev_net(dev), saddr,
							   dev, 1);
		if (ifp) {
			if (ifp->flags & IFA_F_OPTIMISTIC)  {
				send_sllao = 0;
			}
			in6_ifa_put(ifp);
		} else {
			send_sllao = 0;
		}
	}
#endif
	__ndisc_send(dev, NULL, daddr, saddr,
		     &icmp6h, NULL,
		     send_sllao ? ND_OPT_SOURCE_LL_ADDR : 0);
}