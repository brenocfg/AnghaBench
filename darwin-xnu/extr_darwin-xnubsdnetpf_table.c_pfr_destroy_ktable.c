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
struct pfr_ktable {TYPE_1__* pfrkt_rs; struct pfr_ktable* pfrkt_shadow; int /*<<< orphan*/ * pfrkt_ip6; int /*<<< orphan*/ * pfrkt_ip4; } ;
struct pfr_kentryworkq {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  M_RTABLE ; 
 int /*<<< orphan*/  _FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pf_remove_if_empty_ruleset (TYPE_1__*) ; 
 int /*<<< orphan*/  pfr_clean_node_mask (struct pfr_ktable*,struct pfr_kentryworkq*) ; 
 int /*<<< orphan*/  pfr_destroy_kentries (struct pfr_kentryworkq*) ; 
 int /*<<< orphan*/  pfr_enqueue_addrs (struct pfr_ktable*,struct pfr_kentryworkq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_ktable_pl ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pfr_ktable*) ; 

__attribute__((used)) static void
pfr_destroy_ktable(struct pfr_ktable *kt, int flushaddr)
{
	struct pfr_kentryworkq	 addrq;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (flushaddr) {
		pfr_enqueue_addrs(kt, &addrq, NULL, 0);
		pfr_clean_node_mask(kt, &addrq);
		pfr_destroy_kentries(&addrq);
	}
	if (kt->pfrkt_ip4 != NULL)
		_FREE((caddr_t)kt->pfrkt_ip4, M_RTABLE);
	if (kt->pfrkt_ip6 != NULL)
		_FREE((caddr_t)kt->pfrkt_ip6, M_RTABLE);
	if (kt->pfrkt_shadow != NULL)
		pfr_destroy_ktable(kt->pfrkt_shadow, flushaddr);
	if (kt->pfrkt_rs != NULL) {
		kt->pfrkt_rs->tables--;
		pf_remove_if_empty_ruleset(kt->pfrkt_rs);
	}
	pool_put(&pfr_ktable_pl, kt);
}