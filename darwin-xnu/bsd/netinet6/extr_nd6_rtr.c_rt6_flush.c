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
struct radix_node_head {int /*<<< orphan*/  (* rnh_walktree ) (struct radix_node_head*,int /*<<< orphan*/ ,void*) ;} ;
struct in6_addr {int /*<<< orphan*/ * s6_addr16; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 size_t AF_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (struct in6_addr*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rt6_deleteroute ; 
 struct radix_node_head** rt_tables ; 
 int /*<<< orphan*/  stub1 (struct radix_node_head*,int /*<<< orphan*/ ,void*) ; 

void
rt6_flush(
	struct in6_addr *gateway,
	struct ifnet *ifp)
{
	struct radix_node_head *rnh = rt_tables[AF_INET6];

	/* We'll care only link-local addresses */
	if (!IN6_IS_ADDR_LINKLOCAL(gateway)) {
		return;
	}
	lck_mtx_lock(rnh_lock);
	/* XXX: hack for KAME's link-local address kludge */
	gateway->s6_addr16[1] = htons(ifp->if_index);

	rnh->rnh_walktree(rnh, rt6_deleteroute, (void *)gateway);
	lck_mtx_unlock(rnh_lock);
}