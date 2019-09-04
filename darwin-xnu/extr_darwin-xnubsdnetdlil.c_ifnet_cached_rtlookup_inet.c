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
struct in_addr {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; int sin_len; struct in_addr sin_addr; } ;
struct sockaddr {int dummy; } ;
struct rtentry {int dummy; } ;
struct route {struct rtentry* ro_rt; int /*<<< orphan*/  ro_dst; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ROUTE_RELEASE (struct route*) ; 
 scalar_t__ ROUTE_UNUSABLE (struct route*) ; 
 int /*<<< orphan*/  RT_ADDREF (struct rtentry*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ifp_src_route_copyin (struct ifnet*,struct route*) ; 
 int /*<<< orphan*/  ifp_src_route_copyout (struct ifnet*,struct route*) ; 
 struct rtentry* rtalloc1_scoped (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rtentry *
ifnet_cached_rtlookup_inet(struct ifnet	*ifp, struct in_addr src_ip)
{
	struct route		src_rt;
	struct sockaddr_in	*dst;

	dst = (struct sockaddr_in *)(void *)(&src_rt.ro_dst);

	ifp_src_route_copyout(ifp, &src_rt);

	if (ROUTE_UNUSABLE(&src_rt) || src_ip.s_addr != dst->sin_addr.s_addr) {
		ROUTE_RELEASE(&src_rt);
		if (dst->sin_family != AF_INET) {
			bzero(&src_rt.ro_dst, sizeof (src_rt.ro_dst));
			dst->sin_len = sizeof (src_rt.ro_dst);
			dst->sin_family = AF_INET;
		}
		dst->sin_addr = src_ip;

		VERIFY(src_rt.ro_rt == NULL);
		src_rt.ro_rt = rtalloc1_scoped((struct sockaddr *)dst,
		    0, 0, ifp->if_index);

		if (src_rt.ro_rt != NULL) {
			/* retain a ref, copyin consumes one */
			struct rtentry	*rte = src_rt.ro_rt;
			RT_ADDREF(rte);
			ifp_src_route_copyin(ifp, &src_rt);
			src_rt.ro_rt = rte;
		}
	}

	return (src_rt.ro_rt);
}