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
struct ip6_sf_list {int* sf_count; int sf_crcount; struct ip6_sf_list* sf_next; int /*<<< orphan*/  sf_addr; scalar_t__ sf_oldin; } ;
struct ifmcaddr6 {int* mca_sfcount; struct ip6_sf_list* mca_tomb; struct ip6_sf_list* mca_sources; TYPE_1__* idev; } ;
struct TYPE_2__ {int mc_qrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ip6_sf_list*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sf_setstate(struct ifmcaddr6 *pmc)
{
	struct ip6_sf_list *psf, *dpsf;
	int mca_xcount = pmc->mca_sfcount[MCAST_EXCLUDE];
	int qrv = pmc->idev->mc_qrv;
	int new_in, rv;

	rv = 0;
	for (psf=pmc->mca_sources; psf; psf=psf->sf_next) {
		if (pmc->mca_sfcount[MCAST_EXCLUDE]) {
			new_in = mca_xcount == psf->sf_count[MCAST_EXCLUDE] &&
				!psf->sf_count[MCAST_INCLUDE];
		} else
			new_in = psf->sf_count[MCAST_INCLUDE] != 0;
		if (new_in) {
			if (!psf->sf_oldin) {
				struct ip6_sf_list *prev = NULL;

				for (dpsf=pmc->mca_tomb; dpsf;
				     dpsf=dpsf->sf_next) {
					if (ipv6_addr_equal(&dpsf->sf_addr,
					    &psf->sf_addr))
						break;
					prev = dpsf;
				}
				if (dpsf) {
					if (prev)
						prev->sf_next = dpsf->sf_next;
					else
						pmc->mca_tomb = dpsf->sf_next;
					kfree(dpsf);
				}
				psf->sf_crcount = qrv;
				rv++;
			}
		} else if (psf->sf_oldin) {
			psf->sf_crcount = 0;
			/*
			 * add or update "delete" records if an active filter
			 * is now inactive
			 */
			for (dpsf=pmc->mca_tomb; dpsf; dpsf=dpsf->sf_next)
				if (ipv6_addr_equal(&dpsf->sf_addr,
				    &psf->sf_addr))
					break;
			if (!dpsf) {
				dpsf = (struct ip6_sf_list *)
					kmalloc(sizeof(*dpsf), GFP_ATOMIC);
				if (!dpsf)
					continue;
				*dpsf = *psf;
				/* pmc->mca_lock held by callers */
				dpsf->sf_next = pmc->mca_tomb;
				pmc->mca_tomb = dpsf;
			}
			dpsf->sf_crcount = qrv;
			rv++;
		}
	}
	return rv;
}