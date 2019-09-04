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
struct pfr_kentry {int /*<<< orphan*/  pfrke_sa; int /*<<< orphan*/  pfrke_net; int /*<<< orphan*/  pfrke_af; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ KENTRY_NETWORK (struct pfr_kentry*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_prepare_network (union sockaddr_union*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct radix_node* rn_delete (int /*<<< orphan*/ *,union sockaddr_union*,struct radix_node_head*) ; 

__attribute__((used)) static int
pfr_unroute_kentry(struct pfr_ktable *kt, struct pfr_kentry *ke)
{
	union sockaddr_union	 mask;
	struct radix_node	*rn;
	struct radix_node_head	*head;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (ke->pfrke_af == AF_INET)
		head = kt->pfrkt_ip4;
	else if (ke->pfrke_af == AF_INET6)
		head = kt->pfrkt_ip6;
	else
		return (-1);

	if (KENTRY_NETWORK(ke)) {
		pfr_prepare_network(&mask, ke->pfrke_af, ke->pfrke_net);
		rn = rn_delete(&ke->pfrke_sa, &mask, head);
	} else
		rn = rn_delete(&ke->pfrke_sa, NULL, head);

	if (rn == NULL) {
		printf("pfr_unroute_kentry: delete failed.\n");
		return (-1);
	}
	return (0);
}