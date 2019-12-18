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
struct ip6_sf_list {scalar_t__* sf_count; struct ip6_sf_list* sf_next; int /*<<< orphan*/  sf_crcount; scalar_t__ sf_oldin; int /*<<< orphan*/  sf_addr; } ;
struct inet6_dev {int /*<<< orphan*/  mc_qrv; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {int mca_flags; struct ip6_sf_list* mca_tomb; struct ip6_sf_list* mca_sources; struct inet6_dev* idev; } ;

/* Variables and functions */
 int ESRCH ; 
 int MAF_NOREPORT ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int /*<<< orphan*/  MLD_V1_SEEN (struct inet6_dev*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  kfree (struct ip6_sf_list*) ; 

__attribute__((used)) static int ip6_mc_del1_src(struct ifmcaddr6 *pmc, int sfmode,
	struct in6_addr *psfsrc)
{
	struct ip6_sf_list *psf, *psf_prev;
	int rv = 0;

	psf_prev = NULL;
	for (psf=pmc->mca_sources; psf; psf=psf->sf_next) {
		if (ipv6_addr_equal(&psf->sf_addr, psfsrc))
			break;
		psf_prev = psf;
	}
	if (!psf || psf->sf_count[sfmode] == 0) {
		/* source filter not found, or count wrong =>  bug */
		return -ESRCH;
	}
	psf->sf_count[sfmode]--;
	if (!psf->sf_count[MCAST_INCLUDE] && !psf->sf_count[MCAST_EXCLUDE]) {
		struct inet6_dev *idev = pmc->idev;

		/* no more filters for this source */
		if (psf_prev)
			psf_prev->sf_next = psf->sf_next;
		else
			pmc->mca_sources = psf->sf_next;
		if (psf->sf_oldin && !(pmc->mca_flags & MAF_NOREPORT) &&
		    !MLD_V1_SEEN(idev)) {
			psf->sf_crcount = idev->mc_qrv;
			psf->sf_next = pmc->mca_tomb;
			pmc->mca_tomb = psf;
			rv = 1;
		} else
			kfree(psf);
	}
	return rv;
}