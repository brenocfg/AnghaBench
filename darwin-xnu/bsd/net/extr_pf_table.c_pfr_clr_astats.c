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
struct pfr_table {int dummy; } ;
struct pfr_ktable {int pfrkt_flags; } ;
struct pfr_kentryworkq {int dummy; } ;
struct pfr_kentry {int dummy; } ;
struct pfr_addr {int /*<<< orphan*/  pfra_fback; } ;
typedef  int /*<<< orphan*/  ad ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT_FLAGS (int,int) ; 
 scalar_t__ COPYIN (int,struct pfr_addr*,int,int) ; 
 scalar_t__ COPYOUT (struct pfr_addr*,int,int,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  PFR_FB_CLEARED ; 
 int /*<<< orphan*/  PFR_FB_NONE ; 
 int PFR_FLAG_ATOMIC ; 
 int PFR_FLAG_DUMMY ; 
 int PFR_FLAG_FEEDBACK ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  SLIST_INIT (struct pfr_kentryworkq*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct pfr_kentryworkq*,struct pfr_kentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_clstats_kentries (struct pfr_kentryworkq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pfr_kentry* pfr_lookup_addr (struct pfr_ktable*,struct pfr_addr*,int) ; 
 struct pfr_ktable* pfr_lookup_table (struct pfr_table*) ; 
 int /*<<< orphan*/  pfr_reset_feedback (int,int,int) ; 
 scalar_t__ pfr_validate_addr (struct pfr_addr*) ; 
 scalar_t__ pfr_validate_table (struct pfr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfrke_workq ; 
 int /*<<< orphan*/  senderr (int) ; 

int
pfr_clr_astats(struct pfr_table *tbl, user_addr_t _addr, int size,
    int *nzero, int flags)
{
	struct pfr_ktable	*kt;
	struct pfr_kentryworkq	 workq;
	struct pfr_kentry	*p;
	struct pfr_addr		 ad;
	user_addr_t		 addr = _addr;
	int			 i, rv, xzero = 0;

	ACCEPT_FLAGS(flags, PFR_FLAG_ATOMIC | PFR_FLAG_DUMMY |
	    PFR_FLAG_FEEDBACK);
	if (pfr_validate_table(tbl, 0, 0))
		return (EINVAL);
	kt = pfr_lookup_table(tbl);
	if (kt == NULL || !(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (ESRCH);
	SLIST_INIT(&workq);
	for (i = 0; i < size; i++, addr += sizeof (ad)) {
		if (COPYIN(addr, &ad, sizeof (ad), flags))
			senderr(EFAULT);
		if (pfr_validate_addr(&ad))
			senderr(EINVAL);
		p = pfr_lookup_addr(kt, &ad, 1);
		if (flags & PFR_FLAG_FEEDBACK) {
			ad.pfra_fback = (p != NULL) ?
			    PFR_FB_CLEARED : PFR_FB_NONE;
			if (COPYOUT(&ad, addr, sizeof (ad), flags))
				senderr(EFAULT);
		}
		if (p != NULL) {
			SLIST_INSERT_HEAD(&workq, p, pfrke_workq);
			xzero++;
		}
	}

	if (!(flags & PFR_FLAG_DUMMY)) {
		pfr_clstats_kentries(&workq, 0, 0);
	}
	if (nzero != NULL)
		*nzero = xzero;
	return (0);
_bad:
	if (flags & PFR_FLAG_FEEDBACK)
		pfr_reset_feedback(_addr, size, flags);
	return (rv);
}