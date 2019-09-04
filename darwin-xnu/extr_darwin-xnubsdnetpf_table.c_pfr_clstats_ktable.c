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
typedef  int /*<<< orphan*/  u_int64_t ;
struct pfr_ktable {int /*<<< orphan*/  pfrkt_tzero; scalar_t__ pfrkt_nomatch; scalar_t__ pfrkt_match; int /*<<< orphan*/  pfrkt_bytes; int /*<<< orphan*/  pfrkt_packets; } ;
struct pfr_kentryworkq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_clstats_kentries (struct pfr_kentryworkq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_enqueue_addrs (struct pfr_ktable*,struct pfr_kentryworkq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfr_clstats_ktable(struct pfr_ktable *kt, u_int64_t tzero, int recurse)
{
	struct pfr_kentryworkq	 addrq;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (recurse) {
		pfr_enqueue_addrs(kt, &addrq, NULL, 0);
		pfr_clstats_kentries(&addrq, tzero, 0);
	}
	bzero(kt->pfrkt_packets, sizeof (kt->pfrkt_packets));
	bzero(kt->pfrkt_bytes, sizeof (kt->pfrkt_bytes));
	kt->pfrkt_match = kt->pfrkt_nomatch = 0;
	kt->pfrkt_tzero = tzero;
}