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
struct ip_sf_list {scalar_t__ sf_inaddr; int* sf_count; struct ip_sf_list* sf_next; } ;
struct ip_mc_list {int /*<<< orphan*/  interface; struct ip_sf_list* sources; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ip_rt_multicast_event (int /*<<< orphan*/ ) ; 
 struct ip_sf_list* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_mc_add1_src(struct ip_mc_list *pmc, int sfmode,
	__be32 *psfsrc, int delta)
{
	struct ip_sf_list *psf, *psf_prev;

	psf_prev = NULL;
	for (psf=pmc->sources; psf; psf=psf->sf_next) {
		if (psf->sf_inaddr == *psfsrc)
			break;
		psf_prev = psf;
	}
	if (!psf) {
		psf = kzalloc(sizeof(*psf), GFP_ATOMIC);
		if (!psf)
			return -ENOBUFS;
		psf->sf_inaddr = *psfsrc;
		if (psf_prev) {
			psf_prev->sf_next = psf;
		} else
			pmc->sources = psf;
	}
	psf->sf_count[sfmode]++;
	if (psf->sf_count[sfmode] == 1) {
		ip_rt_multicast_event(pmc->interface);
	}
	return 0;
}