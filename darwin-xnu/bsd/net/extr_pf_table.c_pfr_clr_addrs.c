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
struct pfr_table {int dummy; } ;
struct pfr_ktable {int pfrkt_flags; int pfrkt_cnt; } ;
struct pfr_kentryworkq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT_FLAGS (int,int) ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int PFR_FLAG_ATOMIC ; 
 int PFR_FLAG_DUMMY ; 
 int PFR_FLAG_USERIOCTL ; 
 int PFR_TFLAG_ACTIVE ; 
 int PFR_TFLAG_CONST ; 
 int /*<<< orphan*/  pfr_enqueue_addrs (struct pfr_ktable*,struct pfr_kentryworkq*,int*,int /*<<< orphan*/ ) ; 
 struct pfr_ktable* pfr_lookup_table (struct pfr_table*) ; 
 int /*<<< orphan*/  pfr_remove_kentries (struct pfr_ktable*,struct pfr_kentryworkq*) ; 
 scalar_t__ pfr_validate_table (struct pfr_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
pfr_clr_addrs(struct pfr_table *tbl, int *ndel, int flags)
{
	struct pfr_ktable	*kt;
	struct pfr_kentryworkq	 workq;

	ACCEPT_FLAGS(flags, PFR_FLAG_ATOMIC | PFR_FLAG_DUMMY);
	if (pfr_validate_table(tbl, 0, flags & PFR_FLAG_USERIOCTL))
		return (EINVAL);
	kt = pfr_lookup_table(tbl);
	if (kt == NULL || !(kt->pfrkt_flags & PFR_TFLAG_ACTIVE))
		return (ESRCH);
	if (kt->pfrkt_flags & PFR_TFLAG_CONST)
		return (EPERM);
	pfr_enqueue_addrs(kt, &workq, ndel, 0);

	if (!(flags & PFR_FLAG_DUMMY)) {
		pfr_remove_kentries(kt, &workq);
		if (kt->pfrkt_cnt) {
			printf("pfr_clr_addrs: corruption detected (%d).\n",
			    kt->pfrkt_cnt);
			kt->pfrkt_cnt = 0;
		}
	}
	return (0);
}