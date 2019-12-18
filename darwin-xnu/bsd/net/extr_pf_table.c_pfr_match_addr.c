#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pfr_ktable {int pfrkt_flags; int /*<<< orphan*/  pfrkt_nomatch; int /*<<< orphan*/  pfrkt_match; int /*<<< orphan*/  pfrkt_ip6; int /*<<< orphan*/  pfrkt_ip4; struct pfr_ktable* pfrkt_root; } ;
struct pfr_kentry {int /*<<< orphan*/  pfrke_not; } ;
struct pf_addr {int /*<<< orphan*/ * addr32; } ;
typedef  int sa_family_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; TYPE_1__ sin_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  KENTRY_RNF_ROOT (struct pfr_kentry*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  bcopy (struct pf_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pf_lock ; 
 TYPE_2__ pfr_sin ; 
 TYPE_2__ pfr_sin6 ; 
 scalar_t__ rn_match (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
pfr_match_addr(struct pfr_ktable *kt, struct pf_addr *a, sa_family_t af)
{
	struct pfr_kentry	*ke = NULL;
	int			 match;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE) && kt->pfrkt_root != NULL)
		kt = kt->pfrkt_root;
	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (0);

	switch (af) {
#if INET
	case AF_INET:
		pfr_sin.sin_addr.s_addr = a->addr32[0];
		ke = (struct pfr_kentry *)rn_match(&pfr_sin, kt->pfrkt_ip4);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		bcopy(a, &pfr_sin6.sin6_addr, sizeof (pfr_sin6.sin6_addr));
		ke = (struct pfr_kentry *)rn_match(&pfr_sin6, kt->pfrkt_ip6);
		if (ke && KENTRY_RNF_ROOT(ke))
			ke = NULL;
		break;
#endif /* INET6 */
	}
	match = (ke && !ke->pfrke_not);
	if (match)
		kt->pfrkt_match++;
	else
		kt->pfrkt_nomatch++;
	return (match);
}