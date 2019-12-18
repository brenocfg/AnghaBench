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
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rdma_dev_addr {scalar_t__ bound_dev_if; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_check_linklocal(struct rdma_dev_addr *dev_addr,
			       struct sockaddr *addr)
{
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	struct sockaddr_in6 *sin6;

	if (addr->sa_family != AF_INET6)
		return 0;

	sin6 = (struct sockaddr_in6 *) addr;
	if ((ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL) &&
	    !sin6->sin6_scope_id)
			return -EINVAL;

	dev_addr->bound_dev_if = sin6->sin6_scope_id;
#endif
	return 0;
}