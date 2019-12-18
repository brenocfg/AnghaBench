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
struct ip6_sf_list {struct ip6_sf_list* sf_next; } ;
struct ifmcaddr6 {size_t mca_sfmode; int* mca_sfcount; struct ip6_sf_list* mca_sources; struct ip6_sf_list* mca_tomb; } ;

/* Variables and functions */
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int /*<<< orphan*/  kfree (struct ip6_sf_list*) ; 

__attribute__((used)) static void ip6_mc_clear_src(struct ifmcaddr6 *pmc)
{
	struct ip6_sf_list *psf, *nextpsf;

	for (psf=pmc->mca_tomb; psf; psf=nextpsf) {
		nextpsf = psf->sf_next;
		kfree(psf);
	}
	pmc->mca_tomb = NULL;
	for (psf=pmc->mca_sources; psf; psf=nextpsf) {
		nextpsf = psf->sf_next;
		kfree(psf);
	}
	pmc->mca_sources = NULL;
	pmc->mca_sfmode = MCAST_EXCLUDE;
	pmc->mca_sfcount[MCAST_INCLUDE] = 0;
	pmc->mca_sfcount[MCAST_EXCLUDE] = 1;
}