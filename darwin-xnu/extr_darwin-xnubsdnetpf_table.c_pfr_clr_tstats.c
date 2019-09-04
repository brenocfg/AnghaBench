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
typedef  int user_addr_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct pfr_ktableworkq {int dummy; } ;
struct pfr_ktable {int /*<<< orphan*/  pfrkt_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT_FLAGS (int,int) ; 
 scalar_t__ COPYIN (int,int /*<<< orphan*/ *,int,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int PFR_FLAG_ADDRSTOO ; 
 int PFR_FLAG_ATOMIC ; 
 int PFR_FLAG_DUMMY ; 
 struct pfr_ktable* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfr_ktable*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct pfr_ktableworkq*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct pfr_ktableworkq*,struct pfr_ktable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_calendar_time_second () ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_clstats_ktables (struct pfr_ktableworkq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfr_ktablehead ; 
 int /*<<< orphan*/  pfr_ktables ; 
 int /*<<< orphan*/  pfr_table_copyin_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ pfr_validate_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfrkt_workq ; 

int
pfr_clr_tstats(user_addr_t tbl, int size, int *nzero, int flags)
{
	struct pfr_ktableworkq	 workq;
	struct pfr_ktable	*p, key;
	int			 i, xzero = 0;
	u_int64_t		 tzero = pf_calendar_time_second();

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	ACCEPT_FLAGS(flags, PFR_FLAG_ATOMIC | PFR_FLAG_DUMMY |
	    PFR_FLAG_ADDRSTOO);
	SLIST_INIT(&workq);
	for (i = 0; i < size; i++, tbl += sizeof (key.pfrkt_t)) {
		if (COPYIN(tbl, &key.pfrkt_t, sizeof (key.pfrkt_t), flags))
			return (EFAULT);
		pfr_table_copyin_cleanup(&key.pfrkt_t);
		if (pfr_validate_table(&key.pfrkt_t, 0, 0))
			return (EINVAL);
		p = RB_FIND(pfr_ktablehead, &pfr_ktables, &key);
		if (p != NULL) {
			SLIST_INSERT_HEAD(&workq, p, pfrkt_workq);
			xzero++;
		}
	}
	if (!(flags & PFR_FLAG_DUMMY)) {
		pfr_clstats_ktables(&workq, tzero, flags & PFR_FLAG_ADDRSTOO);
	}
	if (nzero != NULL)
		*nzero = xzero;
	return (0);
}