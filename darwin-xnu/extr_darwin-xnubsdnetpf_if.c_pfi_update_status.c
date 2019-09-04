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
struct pfi_kif_cmp {int /*<<< orphan*/  pfik_name; } ;
struct pfi_kif {int /*<<< orphan*/  pfik_tzero; scalar_t__*** pfik_bytes; scalar_t__*** pfik_packets; } ;
struct pf_status {scalar_t__*** bcounters; scalar_t__*** pcounters; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 struct pfi_kif* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/  bzero (scalar_t__***,int) ; 
 int /*<<< orphan*/  pf_calendar_time_second () ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfi_ifhead ; 
 int /*<<< orphan*/  pfi_ifs ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

void
pfi_update_status(const char *name, struct pf_status *pfs)
{
	struct pfi_kif		*p;
	struct pfi_kif_cmp	 key;
	int			 i, j, k;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	strlcpy(key.pfik_name, name, sizeof (key.pfik_name));
	p = RB_FIND(pfi_ifhead, &pfi_ifs, (struct pfi_kif *)(void *)&key);
	if (p == NULL)
		return;

	if (pfs != NULL) {
		bzero(pfs->pcounters, sizeof (pfs->pcounters));
		bzero(pfs->bcounters, sizeof (pfs->bcounters));
		for (i = 0; i < 2; i++)
			for (j = 0; j < 2; j++)
				for (k = 0; k < 2; k++) {
					pfs->pcounters[i][j][k] +=
						p->pfik_packets[i][j][k];
					pfs->bcounters[i][j] +=
						p->pfik_bytes[i][j][k];
				}
	} else {
		/* just clear statistics */
		bzero(p->pfik_packets, sizeof (p->pfik_packets));
		bzero(p->pfik_bytes, sizeof (p->pfik_bytes));
		p->pfik_tzero = pf_calendar_time_second();
	}
}