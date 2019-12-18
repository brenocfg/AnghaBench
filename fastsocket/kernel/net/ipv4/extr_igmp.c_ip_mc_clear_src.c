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
struct ip_sf_list {struct ip_sf_list* sf_next; } ;
struct ip_mc_list {size_t sfmode; int* sfcount; struct ip_sf_list* sources; struct ip_sf_list* tomb; } ;

/* Variables and functions */
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int /*<<< orphan*/  kfree (struct ip_sf_list*) ; 

__attribute__((used)) static void ip_mc_clear_src(struct ip_mc_list *pmc)
{
	struct ip_sf_list *psf, *nextpsf;

	for (psf=pmc->tomb; psf; psf=nextpsf) {
		nextpsf = psf->sf_next;
		kfree(psf);
	}
	pmc->tomb = NULL;
	for (psf=pmc->sources; psf; psf=nextpsf) {
		nextpsf = psf->sf_next;
		kfree(psf);
	}
	pmc->sources = NULL;
	pmc->sfmode = MCAST_EXCLUDE;
	pmc->sfcount[MCAST_INCLUDE] = 0;
	pmc->sfcount[MCAST_EXCLUDE] = 1;
}