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
typedef  int /*<<< orphan*/  w ;
struct pfr_walktree {int pfrw_cnt; int /*<<< orphan*/  pfrw_op; } ;
struct pfr_ktable {int dummy; } ;
struct pfr_kentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  PFRW_POOL_GET ; 
 int /*<<< orphan*/  bzero (struct pfr_walktree*,int) ; 
 int /*<<< orphan*/  pf_lock ; 

__attribute__((used)) static struct pfr_kentry *
pfr_kentry_byidx(struct pfr_ktable *kt, int idx, int af)
{
	struct pfr_walktree	w;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	bzero(&w, sizeof (w));
	w.pfrw_op = PFRW_POOL_GET;
	w.pfrw_cnt = idx;

	switch (af) {
#if INET
	case AF_INET:
		(void) kt->pfrkt_ip4->rnh_walktree(kt->pfrkt_ip4,
		    pfr_walktree, &w);
		return (w.pfrw_kentry);
#endif /* INET */
#if INET6
	case AF_INET6:
		(void) kt->pfrkt_ip6->rnh_walktree(kt->pfrkt_ip6,
		    pfr_walktree, &w);
		return (w.pfrw_kentry);
#endif /* INET6 */
	default:
		return (NULL);
	}
}