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
struct ip_sf_list {scalar_t__ sf_inaddr; scalar_t__* sf_count; struct ip_sf_list* sf_next; scalar_t__ sf_crcount; scalar_t__ sf_oldin; } ;
struct ip_mc_list {struct ip_sf_list* tomb; struct ip_sf_list* sources; struct in_device* interface; } ;
struct in_device {scalar_t__ mr_qrv; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ IGMP_Unsolicited_Report_Count ; 
 int /*<<< orphan*/  IGMP_V1_SEEN (struct in_device*) ; 
 int /*<<< orphan*/  IGMP_V2_SEEN (struct in_device*) ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int /*<<< orphan*/  ip_rt_multicast_event (struct in_device*) ; 
 int /*<<< orphan*/  kfree (struct ip_sf_list*) ; 

__attribute__((used)) static int ip_mc_del1_src(struct ip_mc_list *pmc, int sfmode,
	__be32 *psfsrc)
{
	struct ip_sf_list *psf, *psf_prev;
	int rv = 0;

	psf_prev = NULL;
	for (psf=pmc->sources; psf; psf=psf->sf_next) {
		if (psf->sf_inaddr == *psfsrc)
			break;
		psf_prev = psf;
	}
	if (!psf || psf->sf_count[sfmode] == 0) {
		/* source filter not found, or count wrong =>  bug */
		return -ESRCH;
	}
	psf->sf_count[sfmode]--;
	if (psf->sf_count[sfmode] == 0) {
		ip_rt_multicast_event(pmc->interface);
	}
	if (!psf->sf_count[MCAST_INCLUDE] && !psf->sf_count[MCAST_EXCLUDE]) {
#ifdef CONFIG_IP_MULTICAST
		struct in_device *in_dev = pmc->interface;
#endif

		/* no more filters for this source */
		if (psf_prev)
			psf_prev->sf_next = psf->sf_next;
		else
			pmc->sources = psf->sf_next;
#ifdef CONFIG_IP_MULTICAST
		if (psf->sf_oldin &&
		    !IGMP_V1_SEEN(in_dev) && !IGMP_V2_SEEN(in_dev)) {
			psf->sf_crcount = in_dev->mr_qrv ? in_dev->mr_qrv :
				IGMP_Unsolicited_Report_Count;
			psf->sf_next = pmc->tomb;
			pmc->tomb = psf;
			rv = 1;
		} else
#endif
			kfree(psf);
	}
	return rv;
}