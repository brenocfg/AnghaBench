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
typedef  int /*<<< orphan*/  u ;
struct pfi_uif {int /*<<< orphan*/  pfik_rules; int /*<<< orphan*/  pfik_states; int /*<<< orphan*/  pfik_flags; scalar_t__ pfik_tzero; int /*<<< orphan*/  pfik_bytes; int /*<<< orphan*/  pfik_packets; int /*<<< orphan*/  pfik_name; } ;
struct pfi_kif {int /*<<< orphan*/  pfik_rules; int /*<<< orphan*/  pfik_states; int /*<<< orphan*/  pfik_flags; scalar_t__ pfik_tzero; int /*<<< orphan*/  pfik_bytes; int /*<<< orphan*/  pfik_packets; int /*<<< orphan*/  pfik_name; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  PFI_KIF_REF_RULE ; 
 struct pfi_kif* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pfi_kif* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct pfi_uif*,int) ; 
 scalar_t__ copyout (struct pfi_uif*,int,int) ; 
 scalar_t__ pf_calendar_time_second () ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfi_ifhead ; 
 int /*<<< orphan*/  pfi_ifs ; 
 int /*<<< orphan*/  pfi_kif_ref (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfi_kif_unref (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 scalar_t__ pfi_skip_if (char const*,struct pfi_kif*) ; 

int
pfi_get_ifaces(const char *name, user_addr_t buf, int *size)
{
	struct pfi_kif	 *p, *nextp;
	int		 n = 0;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	for (p = RB_MIN(pfi_ifhead, &pfi_ifs); p; p = nextp) {
		nextp = RB_NEXT(pfi_ifhead, &pfi_ifs, p);
		if (pfi_skip_if(name, p))
			continue;
		if (*size > n++) {
			struct pfi_uif u;

			if (!p->pfik_tzero)
				p->pfik_tzero = pf_calendar_time_second();
			pfi_kif_ref(p, PFI_KIF_REF_RULE);

			/* return the user space version of pfi_kif */
			bzero(&u, sizeof (u));
			bcopy(p->pfik_name, &u.pfik_name, sizeof (u.pfik_name));
			bcopy(p->pfik_packets, &u.pfik_packets,
			    sizeof (u.pfik_packets));
			bcopy(p->pfik_bytes, &u.pfik_bytes,
			    sizeof (u.pfik_bytes));
			u.pfik_tzero = p->pfik_tzero;
			u.pfik_flags = p->pfik_flags;
			u.pfik_states = p->pfik_states;
			u.pfik_rules = p->pfik_rules;

			if (copyout(&u, buf, sizeof (u))) {
				pfi_kif_unref(p, PFI_KIF_REF_RULE);
				return (EFAULT);
			}
			buf += sizeof (u);
			nextp = RB_NEXT(pfi_ifhead, &pfi_ifs, p);
			pfi_kif_unref(p, PFI_KIF_REF_RULE);
		}
	}
	*size = n;
	return (0);
}