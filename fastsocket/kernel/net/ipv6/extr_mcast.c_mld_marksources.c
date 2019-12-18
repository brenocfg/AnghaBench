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
struct ip6_sf_list {int sf_gsresp; int /*<<< orphan*/  sf_addr; struct ip6_sf_list* sf_next; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {scalar_t__ mca_sfmode; int /*<<< orphan*/  mca_flags; struct ip6_sf_list* mca_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAF_GSQUERY ; 
 scalar_t__ MCAST_EXCLUDE ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int mld_xmarksources (struct ifmcaddr6*,int,struct in6_addr*) ; 

__attribute__((used)) static int mld_marksources(struct ifmcaddr6 *pmc, int nsrcs,
	struct in6_addr *srcs)
{
	struct ip6_sf_list *psf;
	int i, scount;

	if (pmc->mca_sfmode == MCAST_EXCLUDE)
		return mld_xmarksources(pmc, nsrcs, srcs);

	/* mark INCLUDE-mode sources */

	scount = 0;
	for (psf=pmc->mca_sources; psf; psf=psf->sf_next) {
		if (scount == nsrcs)
			break;
		for (i=0; i<nsrcs; i++) {
			if (ipv6_addr_equal(&srcs[i], &psf->sf_addr)) {
				psf->sf_gsresp = 1;
				scount++;
				break;
			}
		}
	}
	if (!scount) {
		pmc->mca_flags &= ~MAF_GSQUERY;
		return 0;
	}
	pmc->mca_flags |= MAF_GSQUERY;
	return 1;
}