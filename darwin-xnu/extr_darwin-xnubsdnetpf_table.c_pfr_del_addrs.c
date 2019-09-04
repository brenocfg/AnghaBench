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
struct pfr_ktable {int pfrkt_flags; int pfrkt_cnt; } ;
struct pfr_kentryworkq {int dummy; } ;
struct pfr_kentry {int pfrke_mark; scalar_t__ pfrke_not; } ;
struct pfr_addr {scalar_t__ pfra_not; int /*<<< orphan*/  pfra_fback; } ;
typedef  int /*<<< orphan*/  ad ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT_FLAGS (int,int) ; 
 scalar_t__ COPYIN (int,struct pfr_addr*,int,int) ; 
 scalar_t__ COPYOUT (struct pfr_addr*,int,int,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  PFR_FB_CONFLICT ; 
 int /*<<< orphan*/  PFR_FB_DELETED ; 
 int /*<<< orphan*/  PFR_FB_DUPLICATE ; 
 int /*<<< orphan*/  PFR_FB_NONE ; 
 int PFR_FLAG_ATOMIC ; 
 int PFR_FLAG_DUMMY ; 
 int PFR_FLAG_FEEDBACK ; 
 int PFR_FLAG_USERIOCTL ; 
 int PFR_TFLAG_ACTIVE ; 
 int PFR_TFLAG_CONST ; 
 int /*<<< orphan*/  SLIST_INIT (struct pfr_kentryworkq*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct pfr_kentryworkq*,struct pfr_kentry*,int /*<<< orphan*/ ) ; 
 struct pfr_kentry* pfr_lookup_addr (struct pfr_ktable*,struct pfr_addr*,int) ; 
 struct pfr_ktable* pfr_lookup_table (struct pfr_table*) ; 
 int /*<<< orphan*/  pfr_mark_addrs (struct pfr_ktable*) ; 
 int /*<<< orphan*/  pfr_remove_kentries (struct pfr_ktable*,struct pfr_kentryworkq*) ; 
 int /*<<< orphan*/  pfr_reset_feedback (int,int,int) ; 
 scalar_t__ pfr_validate_addr (struct pfr_addr*) ; 
 scalar_t__ pfr_validate_table (struct pfr_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfrke_workq ; 
 int /*<<< orphan*/  senderr (int) ; 

int
pfr_del_addrs(struct pfr_table *tbl, user_addr_t _addr, int size,
    int *ndel, int flags)
{
	struct pfr_ktable	*kt;
	struct pfr_kentryworkq	 workq;
	struct pfr_kentry	*p;
	struct pfr_addr		 ad;
	user_addr_t		 addr = _addr;
	int			 i, rv, xdel = 0, log = 1;

	ACCEPT_FLAGS(flags, PFR_FLAG_ATOMIC | PFR_FLAG_DUMMY |
	    PFR_FLAG_FEEDBACK);
	if (pfr_validate_table(tbl, 0, flags & PFR_FLAG_USERIOCTL))
		return (EINVAL);
	kt = pfr_lookup_table(tbl);
	if (kt == NULL || !(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (ESRCH);
	if (kt->pfrkt_flags & PFR_TFLAG_CONST)
		return (EPERM);
	/*
	 * there are two algorithms to choose from here.
	 * with:
	 *   n: number of addresses to delete
	 *   N: number of addresses in the table
	 *
	 * one is O(N) and is better for large 'n'
	 * one is O(n*LOG(N)) and is better for small 'n'
	 *
	 * following code try to decide which one is best.
	 */
	for (i = kt->pfrkt_cnt; i > 0; i >>= 1)
		log++;
	if (size > kt->pfrkt_cnt/log) {
		/* full table scan */
		pfr_mark_addrs(kt);
	} else {
		/* iterate over addresses to delete */
		for (i = 0; i < size; i++, addr += sizeof (ad)) {
			if (COPYIN(addr, &ad, sizeof (ad), flags))
				return (EFAULT);
			if (pfr_validate_addr(&ad))
				return (EINVAL);
			p = pfr_lookup_addr(kt, &ad, 1);
			if (p != NULL)
				p->pfrke_mark = 0;
		}
	}
	SLIST_INIT(&workq);
	for (addr = _addr, i = 0; i < size; i++, addr += sizeof (ad)) {
		if (COPYIN(addr, &ad, sizeof (ad), flags))
			senderr(EFAULT);
		if (pfr_validate_addr(&ad))
			senderr(EINVAL);
		p = pfr_lookup_addr(kt, &ad, 1);
		if (flags & PFR_FLAG_FEEDBACK) {
			if (p == NULL)
				ad.pfra_fback = PFR_FB_NONE;
			else if (p->pfrke_not != ad.pfra_not)
				ad.pfra_fback = PFR_FB_CONFLICT;
			else if (p->pfrke_mark)
				ad.pfra_fback = PFR_FB_DUPLICATE;
			else
				ad.pfra_fback = PFR_FB_DELETED;
		}
		if (p != NULL && p->pfrke_not == ad.pfra_not &&
		    !p->pfrke_mark) {
			p->pfrke_mark = 1;
			SLIST_INSERT_HEAD(&workq, p, pfrke_workq);
			xdel++;
		}
		if (flags & PFR_FLAG_FEEDBACK)
			if (COPYOUT(&ad, addr, sizeof (ad), flags))
				senderr(EFAULT);
	}
	if (!(flags & PFR_FLAG_DUMMY)) {
		pfr_remove_kentries(kt, &workq);
	}
	if (ndel != NULL)
		*ndel = xdel;
	return (0);
_bad:
	if (flags & PFR_FLAG_FEEDBACK)
		pfr_reset_feedback(_addr, size, flags);
	return (rv);
}