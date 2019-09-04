#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pf_addr {int dummy; } ;
struct TYPE_13__ {struct pf_rule* ptr; } ;
struct pf_src_node {int af; struct pf_addr raddr; struct pf_addr addr; TYPE_6__ rule; } ;
struct pf_pool {int opts; int af; int tblidx; struct pf_addr counter; struct pf_pooladdr* cur; int /*<<< orphan*/  list; int /*<<< orphan*/  key; } ;
struct pf_rule {int rule_flag; struct pf_pool rpool; } ;
struct TYPE_10__ {struct pf_addr mask; struct pf_addr addr; } ;
struct TYPE_11__ {TYPE_3__ a; } ;
struct TYPE_9__ {TYPE_1__* dyn; int /*<<< orphan*/  tbl; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_4__ v; TYPE_2__ p; } ;
struct pf_pooladdr {TYPE_5__ addr; } ;
typedef  int sa_family_t ;
struct TYPE_14__ {scalar_t__ debug; int /*<<< orphan*/ * scounters; } ;
struct TYPE_8__ {int /*<<< orphan*/  pfid_kt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int PFRULE_RULESRCTRACK ; 
 int /*<<< orphan*/  PF_ACPY (struct pf_addr*,struct pf_addr*,int) ; 
 scalar_t__ PF_ADDR_DYNIFTL ; 
 scalar_t__ PF_ADDR_NOROUTE ; 
 scalar_t__ PF_ADDR_TABLE ; 
 int /*<<< orphan*/  PF_AINC (struct pf_addr*,int) ; 
 scalar_t__ PF_AZERO (struct pf_addr*,int) ; 
 scalar_t__ PF_DEBUG_MISC ; 
 int /*<<< orphan*/  PF_POOLMASK (struct pf_addr*,struct pf_addr*,struct pf_addr*,struct pf_addr*,int) ; 
#define  PF_POOL_BITMASK 132 
#define  PF_POOL_NONE 131 
#define  PF_POOL_RANDOM 130 
#define  PF_POOL_ROUNDROBIN 129 
#define  PF_POOL_SRCHASH 128 
 int PF_POOL_STICKYADDR ; 
 int PF_POOL_TYPEMASK ; 
 struct pf_src_node* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_src_node*) ; 
 size_t SCNT_SRC_NODE_SEARCH ; 
 struct pf_pooladdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pf_pooladdr* TAILQ_NEXT (struct pf_pooladdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pf_hash (struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pf_match_addr (int /*<<< orphan*/ ,struct pf_addr*,struct pf_addr*,struct pf_addr*,int) ; 
 int /*<<< orphan*/  pf_print_host (struct pf_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pf_src_tree ; 
 TYPE_7__ pf_status ; 
 int /*<<< orphan*/  pfr_pool_get (int /*<<< orphan*/ ,int*,struct pf_addr*,struct pf_addr**,struct pf_addr**,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tree_src_tracking ; 

__attribute__((used)) static int
pf_map_addr(sa_family_t af, struct pf_rule *r, struct pf_addr *saddr,
    struct pf_addr *naddr, struct pf_addr *init_addr, struct pf_src_node **sn)
{
	unsigned char		 hash[16];
	struct pf_pool		*rpool = &r->rpool;
	struct pf_addr		*raddr = &rpool->cur->addr.v.a.addr;
	struct pf_addr		*rmask = &rpool->cur->addr.v.a.mask;
	struct pf_pooladdr	*acur = rpool->cur;
	struct pf_src_node	 k;

	if (*sn == NULL && r->rpool.opts & PF_POOL_STICKYADDR &&
	    (r->rpool.opts & PF_POOL_TYPEMASK) != PF_POOL_NONE) {
		k.af = af;
		PF_ACPY(&k.addr, saddr, af);
		if (r->rule_flag & PFRULE_RULESRCTRACK ||
		    r->rpool.opts & PF_POOL_STICKYADDR)
			k.rule.ptr = r;
		else
			k.rule.ptr = NULL;
		pf_status.scounters[SCNT_SRC_NODE_SEARCH]++;
		*sn = RB_FIND(pf_src_tree, &tree_src_tracking, &k);
		if (*sn != NULL && !PF_AZERO(&(*sn)->raddr, rpool->af)) {
			PF_ACPY(naddr, &(*sn)->raddr, rpool->af);
			if (pf_status.debug >= PF_DEBUG_MISC) {
				printf("pf_map_addr: src tracking maps ");
				pf_print_host(&k.addr, 0, af);
				printf(" to ");
				pf_print_host(naddr, 0, rpool->af);
				printf("\n");
			}
			return (0);
		}
	}

	if (rpool->cur->addr.type == PF_ADDR_NOROUTE)
		return (1);
	if (rpool->cur->addr.type == PF_ADDR_DYNIFTL) {
		if (rpool->cur->addr.p.dyn == NULL)
			return (1);
		switch (rpool->af) {
#if INET
		case AF_INET:
			if (rpool->cur->addr.p.dyn->pfid_acnt4 < 1 &&
			    (rpool->opts & PF_POOL_TYPEMASK) !=
			    PF_POOL_ROUNDROBIN)
				return (1);
			raddr = &rpool->cur->addr.p.dyn->pfid_addr4;
			rmask = &rpool->cur->addr.p.dyn->pfid_mask4;
			break;
#endif /* INET */
#if INET6
		case AF_INET6:
			if (rpool->cur->addr.p.dyn->pfid_acnt6 < 1 &&
			    (rpool->opts & PF_POOL_TYPEMASK) !=
			    PF_POOL_ROUNDROBIN)
				return (1);
			raddr = &rpool->cur->addr.p.dyn->pfid_addr6;
			rmask = &rpool->cur->addr.p.dyn->pfid_mask6;
			break;
#endif /* INET6 */
		}
	} else if (rpool->cur->addr.type == PF_ADDR_TABLE) {
		if ((rpool->opts & PF_POOL_TYPEMASK) != PF_POOL_ROUNDROBIN)
			return (1); /* unsupported */
	} else {
		raddr = &rpool->cur->addr.v.a.addr;
		rmask = &rpool->cur->addr.v.a.mask;
	}

	switch (rpool->opts & PF_POOL_TYPEMASK) {
	case PF_POOL_NONE:
		PF_ACPY(naddr, raddr, rpool->af);
		break;
	case PF_POOL_BITMASK:
		ASSERT(af == rpool->af);
		PF_POOLMASK(naddr, raddr, rmask, saddr, af);
		break;
	case PF_POOL_RANDOM:
		if (init_addr != NULL && PF_AZERO(init_addr, rpool->af)) {
			switch (af) {
#if INET
			case AF_INET:
				rpool->counter.addr32[0] = htonl(random());
				break;
#endif /* INET */
#if INET6
			case AF_INET6:
				if (rmask->addr32[3] != 0xffffffff)
					rpool->counter.addr32[3] =
					    RandomULong();
				else
					break;
				if (rmask->addr32[2] != 0xffffffff)
					rpool->counter.addr32[2] =
					    RandomULong();
				else
					break;
				if (rmask->addr32[1] != 0xffffffff)
					rpool->counter.addr32[1] =
					    RandomULong();
				else
					break;
				if (rmask->addr32[0] != 0xffffffff)
					rpool->counter.addr32[0] =
					    RandomULong();
				break;
#endif /* INET6 */
			}
			PF_POOLMASK(naddr, raddr, rmask, &rpool->counter,
				    rpool->af);
			PF_ACPY(init_addr, naddr, rpool->af);

		} else {
			PF_AINC(&rpool->counter, rpool->af);
			PF_POOLMASK(naddr, raddr, rmask, &rpool->counter,
				    rpool->af);
		}
		break;
	case PF_POOL_SRCHASH:
		ASSERT(af == rpool->af);
		PF_POOLMASK(naddr, raddr, rmask, saddr, af);
		pf_hash(saddr, (struct pf_addr *)(void *)&hash,
		    &rpool->key, af);
		PF_POOLMASK(naddr, raddr, rmask,
		    (struct pf_addr *)(void *)&hash, af);
		break;
	case PF_POOL_ROUNDROBIN:
		if (rpool->cur->addr.type == PF_ADDR_TABLE) {
			if (!pfr_pool_get(rpool->cur->addr.p.tbl,
			    &rpool->tblidx, &rpool->counter,
			    &raddr, &rmask, rpool->af))
				goto get_addr;
		} else if (rpool->cur->addr.type == PF_ADDR_DYNIFTL) {
			if (rpool->cur->addr.p.dyn != NULL &&
			    !pfr_pool_get(rpool->cur->addr.p.dyn->pfid_kt,
			    &rpool->tblidx, &rpool->counter,
			    &raddr, &rmask, af))
				goto get_addr;
		} else if (pf_match_addr(0, raddr, rmask, &rpool->counter,
					 rpool->af))
			goto get_addr;

	try_next:
		if ((rpool->cur = TAILQ_NEXT(rpool->cur, entries)) == NULL)
			rpool->cur = TAILQ_FIRST(&rpool->list);
		if (rpool->cur->addr.type == PF_ADDR_TABLE) {
			rpool->tblidx = -1;
			if (pfr_pool_get(rpool->cur->addr.p.tbl,
			    &rpool->tblidx, &rpool->counter,
			    &raddr, &rmask, rpool->af)) {
				/* table contains no address of type
				 * 'rpool->af' */
				if (rpool->cur != acur)
					goto try_next;
				return (1);
			}
		} else if (rpool->cur->addr.type == PF_ADDR_DYNIFTL) {
			rpool->tblidx = -1;
			if (rpool->cur->addr.p.dyn == NULL)
				return (1);
			if (pfr_pool_get(rpool->cur->addr.p.dyn->pfid_kt,
			    &rpool->tblidx, &rpool->counter,
			    &raddr, &rmask, rpool->af)) {
				/* table contains no address of type
				 * 'rpool->af' */
				if (rpool->cur != acur)
					goto try_next;
				return (1);
			}
		} else {
			raddr = &rpool->cur->addr.v.a.addr;
			rmask = &rpool->cur->addr.v.a.mask;
			PF_ACPY(&rpool->counter, raddr, rpool->af);
		}

	get_addr:
		PF_ACPY(naddr, &rpool->counter, rpool->af);
		if (init_addr != NULL && PF_AZERO(init_addr, rpool->af))
			PF_ACPY(init_addr, naddr, rpool->af);
		PF_AINC(&rpool->counter, rpool->af);
		break;
	}
	if (*sn != NULL)
		PF_ACPY(&(*sn)->raddr, naddr, rpool->af);

	if (pf_status.debug >= PF_DEBUG_MISC &&
	    (rpool->opts & PF_POOL_TYPEMASK) != PF_POOL_NONE) {
		printf("pf_map_addr: selected address ");
		pf_print_host(naddr, 0, rpool->af);
		printf("\n");
	}

	return (0);
}