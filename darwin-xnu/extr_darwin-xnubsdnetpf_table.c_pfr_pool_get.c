#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
struct pfr_ktable {int pfrkt_flags; int /*<<< orphan*/  pfrkt_match; int /*<<< orphan*/  pfrkt_ip6; int /*<<< orphan*/  pfrkt_ip4; int /*<<< orphan*/  pfrkt_nomatch; struct pfr_ktable* pfrkt_root; } ;
struct pfr_kentry {int /*<<< orphan*/  pfrke_net; union sockaddr_union pfrke_sa; } ;
struct pf_addr {int dummy; } ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  KENTRY_NETWORK (struct pfr_kentry*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  PF_ACPY (struct pf_addr*,struct pf_addr*,scalar_t__) ; 
 int /*<<< orphan*/  PF_AINC (struct pf_addr*,scalar_t__) ; 
 int /*<<< orphan*/  PF_MATCHA (int /*<<< orphan*/ ,struct pf_addr*,struct pf_addr*,struct pf_addr*,scalar_t__) ; 
 int /*<<< orphan*/  PF_POOLMASK (struct pf_addr*,struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct pf_addr* SUNION2PF (union sockaddr_union*,scalar_t__) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_ffaddr ; 
 struct pfr_kentry* pfr_kentry_byidx (struct pfr_ktable*,int,scalar_t__) ; 
 union sockaddr_union pfr_mask ; 
 int /*<<< orphan*/  pfr_prepare_network (union sockaddr_union*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ pfr_sin ; 
 TYPE_1__ pfr_sin6 ; 
 scalar_t__ rn_match (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
pfr_pool_get(struct pfr_ktable *kt, int *pidx, struct pf_addr *counter,
    struct pf_addr **raddr, struct pf_addr **rmask, sa_family_t af)
{
	struct pfr_kentry	*ke, *ke2;
	struct pf_addr		*addr;
	union sockaddr_union	 mask;
	int			 idx = -1, use_counter = 0;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (af == AF_INET)
		addr = (struct pf_addr *)&pfr_sin.sin_addr;
	else if (af == AF_INET6)
		addr = (struct pf_addr *)&pfr_sin6.sin6_addr;
	else
		return (-1);

	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE) && kt->pfrkt_root != NULL)
		kt = kt->pfrkt_root;
	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (-1);

	if (pidx != NULL)
		idx = *pidx;
	if (counter != NULL && idx >= 0)
		use_counter = 1;
	if (idx < 0)
		idx = 0;

_next_block:
	ke = pfr_kentry_byidx(kt, idx, af);
	if (ke == NULL) {
		kt->pfrkt_nomatch++;
		return (1);
	}
	pfr_prepare_network(&pfr_mask, af, ke->pfrke_net);
	*raddr = SUNION2PF(&ke->pfrke_sa, af);
	*rmask = SUNION2PF(&pfr_mask, af);

	if (use_counter) {
		/* is supplied address within block? */
		if (!PF_MATCHA(0, *raddr, *rmask, counter, af)) {
			/* no, go to next block in table */
			idx++;
			use_counter = 0;
			goto _next_block;
		}
		PF_ACPY(addr, counter, af);
	} else {
		/* use first address of block */
		PF_ACPY(addr, *raddr, af);
	}

	if (!KENTRY_NETWORK(ke)) {
		/* this is a single IP address - no possible nested block */
		PF_ACPY(counter, addr, af);
		*pidx = idx;
		kt->pfrkt_match++;
		return (0);
	}
	for (;;) {
		/* we don't want to use a nested block */
		if (af == AF_INET)
			ke2 = (struct pfr_kentry *)rn_match(&pfr_sin,
			    kt->pfrkt_ip4);
		else if (af == AF_INET6)
			ke2 = (struct pfr_kentry *)rn_match(&pfr_sin6,
			    kt->pfrkt_ip6);
		else
			return (-1); /* never happens */
		/* no need to check KENTRY_RNF_ROOT() here */
		if (ke2 == ke) {
			/* lookup return the same block - perfect */
			PF_ACPY(counter, addr, af);
			*pidx = idx;
			kt->pfrkt_match++;
			return (0);
		}

		/* we need to increase the counter past the nested block */
		pfr_prepare_network(&mask, AF_INET, ke2->pfrke_net);
		PF_POOLMASK(addr, addr, SUNION2PF(&mask, af), &pfr_ffaddr, af);
		PF_AINC(addr, af);
		if (!PF_MATCHA(0, *raddr, *rmask, addr, af)) {
			/* ok, we reached the end of our main block */
			/* go to next block in table */
			idx++;
			use_counter = 0;
			goto _next_block;
		}
	}
}