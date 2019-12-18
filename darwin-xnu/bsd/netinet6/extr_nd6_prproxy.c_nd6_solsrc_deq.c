#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nd_prefix {int ndpr_stateflags; int /*<<< orphan*/  ndpr_prproxy_sols; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {struct in6_addr taddr; } ;
struct nd6_prproxy_soltgt {scalar_t__ soltgt_cnt; int /*<<< orphan*/  soltgt_q; TYPE_1__ soltgt_key; } ;
struct nd6_prproxy_solsrc {struct ifnet* solsrc_ifp; struct in6_addr solsrc_saddr; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NDPRF_IFSCOPE ; 
 int NDPRF_ONLINK ; 
 int NDPRF_PRPROXY ; 
 int /*<<< orphan*/  NDPR_LOCK_ASSERT_HELD (struct nd_prefix*) ; 
 struct nd6_prproxy_soltgt* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nd6_prproxy_soltgt*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct nd6_prproxy_solsrc* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nd6_prproxy_solsrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct in6_addr*,int) ; 
 int /*<<< orphan*/  nd6_solsrc_free (struct nd6_prproxy_solsrc*) ; 
 int /*<<< orphan*/  prproxy_sols_tree ; 
 int /*<<< orphan*/  solsrc_tqe ; 

__attribute__((used)) static boolean_t
nd6_solsrc_deq(struct nd_prefix *pr, struct in6_addr *taddr,
    struct in6_addr *daddr, struct ifnet **ifp)
{
	struct nd6_prproxy_soltgt find, *soltgt;
	struct nd6_prproxy_solsrc *ssrc;

	NDPR_LOCK_ASSERT_HELD(pr);
	VERIFY(!(pr->ndpr_stateflags & NDPRF_IFSCOPE));
	VERIFY((pr->ndpr_stateflags & (NDPRF_ONLINK|NDPRF_PRPROXY)) ==
	    (NDPRF_ONLINK|NDPRF_PRPROXY));

	bzero(daddr, sizeof (*daddr));
	*ifp = NULL;

	find.soltgt_key.taddr = *taddr;		/* search key */

	soltgt = RB_FIND(prproxy_sols_tree, &pr->ndpr_prproxy_sols, &find);
	if (soltgt == NULL || soltgt->soltgt_cnt == 0) {
		VERIFY(soltgt == NULL || TAILQ_EMPTY(&soltgt->soltgt_q));
		return (FALSE);
	}

	VERIFY(soltgt->soltgt_cnt != 0);
	--soltgt->soltgt_cnt;
	ssrc = TAILQ_FIRST(&soltgt->soltgt_q);
	VERIFY(ssrc != NULL);
	TAILQ_REMOVE(&soltgt->soltgt_q, ssrc, solsrc_tqe);
	*daddr = *(&ssrc->solsrc_saddr);
	*ifp = ssrc->solsrc_ifp;
	nd6_solsrc_free(ssrc);

	return (TRUE);
}