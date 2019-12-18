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
struct sock {int dummy; } ;
struct rt6_info {int dummy; } ;
struct net {int dummy; } ;
struct inet6_ifaddr {int flags; } ;
struct in6_addr {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl6_dst; int /*<<< orphan*/  fl6_src; } ;
struct dst_entry {int error; int /*<<< orphan*/  dev; TYPE_1__* neighbour; } ;
struct TYPE_4__ {int /*<<< orphan*/  srcprefs; } ;
struct TYPE_3__ {int nud_state; } ;

/* Variables and functions */
 int ENETUNREACH ; 
 int IFA_F_OPTIMISTIC ; 
 int /*<<< orphan*/  IP6_INC_STATS_BH (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTNOROUTES ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 TYPE_2__* inet6_sk (struct sock*) ; 
 int ip6_route_get_saddr (struct net*,struct rt6_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dst_entry* ip6_route_output (struct net*,struct sock*,struct flowi*) ; 
 scalar_t__ ipv6_addr_any (int /*<<< orphan*/ *) ; 
 struct inet6_ifaddr* ipv6_get_ifaddr (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct flowi*,struct flowi*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct net* sock_net (struct sock*) ; 

__attribute__((used)) static int ip6_dst_lookup_tail(struct sock *sk,
			       struct dst_entry **dst, struct flowi *fl)
{
	int err;
	struct net *net = sock_net(sk);

	if (*dst == NULL)
		*dst = ip6_route_output(net, sk, fl);

	if ((err = (*dst)->error))
		goto out_err_release;

	if (ipv6_addr_any(&fl->fl6_src)) {
		struct rt6_info *rt = (struct rt6_info *) *dst;
		err = ip6_route_get_saddr(net, rt, &fl->fl6_dst,
					  sk ? inet6_sk(sk)->srcprefs : 0,
					  &fl->fl6_src);

		if (err)
			goto out_err_release;
	}

#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	/*
	 * Here if the dst entry we've looked up
	 * has a neighbour entry that is in the INCOMPLETE
	 * state and the src address from the flow is
	 * marked as OPTIMISTIC, we release the found
	 * dst entry and replace it instead with the
	 * dst entry of the nexthop router
	 */
	if ((*dst)->neighbour && !((*dst)->neighbour->nud_state & NUD_VALID)) {
		struct inet6_ifaddr *ifp;
		struct flowi fl_gw;
		int redirect;

		ifp = ipv6_get_ifaddr(net, &fl->fl6_src,
				      (*dst)->dev, 1);

		redirect = (ifp && ifp->flags & IFA_F_OPTIMISTIC);
		if (ifp)
			in6_ifa_put(ifp);

		if (redirect) {
			/*
			 * We need to get the dst entry for the
			 * default router instead
			 */
			dst_release(*dst);
			memcpy(&fl_gw, fl, sizeof(struct flowi));
			memset(&fl_gw.fl6_dst, 0, sizeof(struct in6_addr));
			*dst = ip6_route_output(net, sk, &fl_gw);
			if ((err = (*dst)->error))
				goto out_err_release;
		}
	}
#endif

	return 0;

out_err_release:
	if (err == -ENETUNREACH)
		IP6_INC_STATS_BH(net, NULL, IPSTATS_MIB_OUTNOROUTES);
	dst_release(*dst);
	*dst = NULL;
	return err;
}