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
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
struct radix_node_head {int dummy; } ;
struct radix_node {int dummy; } ;
struct pfr_ktable {struct radix_node_head* pfrkt_ip6; struct radix_node_head* pfrkt_ip4; } ;
struct pfr_kentry {int /*<<< orphan*/  pfrke_node; int /*<<< orphan*/  pfrke_sa; int /*<<< orphan*/  pfrke_net; int /*<<< orphan*/  pfrke_af; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ KENTRY_NETWORK (struct pfr_kentry*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_prepare_network (union sockaddr_union*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radix_node* rn_addroute (int /*<<< orphan*/ *,union sockaddr_union*,struct radix_node_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfr_route_kentry(struct pfr_ktable *kt, struct pfr_kentry *ke)
{
	union sockaddr_union	 mask;
	struct radix_node	*rn;
	struct radix_node_head	*head;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	bzero(ke->pfrke_node, sizeof (ke->pfrke_node));
	if (ke->pfrke_af == AF_INET)
		head = kt->pfrkt_ip4;
	else if (ke->pfrke_af == AF_INET6)
		head = kt->pfrkt_ip6;
	else
		return (-1);

	if (KENTRY_NETWORK(ke)) {
		pfr_prepare_network(&mask, ke->pfrke_af, ke->pfrke_net);
		rn = rn_addroute(&ke->pfrke_sa, &mask, head, ke->pfrke_node);
	} else
		rn = rn_addroute(&ke->pfrke_sa, NULL, head, ke->pfrke_node);

	return (rn == NULL ? -1 : 0);
}