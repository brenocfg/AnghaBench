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
union sockaddr_union {int /*<<< orphan*/  sin6; int /*<<< orphan*/  sin; } ;
struct radix_node_head {int dummy; } ;
struct pfr_ktable {struct radix_node_head* pfrkt_ip6; struct radix_node_head* pfrkt_ip4; } ;
struct pfr_kentry {int dummy; } ;
struct pfr_addr {int /*<<< orphan*/  pfra_net; int /*<<< orphan*/  pfra_af; int /*<<< orphan*/  pfra_ip6addr; int /*<<< orphan*/  pfra_ip4addr; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 scalar_t__ ADDR_NETWORK (struct pfr_addr*) ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  FILLIN_SIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILLIN_SIN6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KENTRY_NETWORK (struct pfr_kentry*) ; 
 scalar_t__ KENTRY_RNF_ROOT (struct pfr_kentry*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  bzero (union sockaddr_union*,int) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_prepare_network (union sockaddr_union*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rn_lookup (union sockaddr_union*,union sockaddr_union*,struct radix_node_head*) ; 
 scalar_t__ rn_match (union sockaddr_union*,struct radix_node_head*) ; 

__attribute__((used)) static struct pfr_kentry *
pfr_lookup_addr(struct pfr_ktable *kt, struct pfr_addr *ad, int exact)
{
	union sockaddr_union	 sa, mask;
	struct radix_node_head	*head;
	struct pfr_kentry	*ke;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	bzero(&sa, sizeof (sa));
	if (ad->pfra_af == AF_INET) {
		FILLIN_SIN(sa.sin, ad->pfra_ip4addr);
		head = kt->pfrkt_ip4;
	} else if (ad->pfra_af == AF_INET6) {
		FILLIN_SIN6(sa.sin6, ad->pfra_ip6addr);
		head = kt->pfrkt_ip6;
	}
	else
		return NULL;
	if (ADDR_NETWORK(ad)) {
		pfr_prepare_network(&mask, ad->pfra_af, ad->pfra_net);
		ke = (struct pfr_kentry *)rn_lookup(&sa, &mask, head);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
	} else {
		ke = (struct pfr_kentry *)rn_match(&sa, head);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
		if (exact && ke && KENTRY_NETWORK(ke))
			ke = NULL;
	}
	return (ke);
}