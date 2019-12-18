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
struct ip_sf_list {scalar_t__ sf_crcount; struct ip_sf_list* sf_next; } ;
struct ip_mc_list {scalar_t__ multiaddr; size_t sfmode; scalar_t__* sfcount; int /*<<< orphan*/  lock; struct ip_sf_list* sources; scalar_t__ crcount; struct in_device* interface; struct ip_mc_list* next; } ;
struct in_device {scalar_t__ mr_ifc_count; scalar_t__ mr_qrv; int /*<<< orphan*/  mc_list_lock; struct ip_mc_list* mc_list; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ENODEV ; 
 int ESRCH ; 
 scalar_t__ IGMP_Unsolicited_Report_Count ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int /*<<< orphan*/  igmp_ifc_event (struct in_device*) ; 
 int ip_mc_add1_src (struct ip_mc_list*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  ip_mc_del1_src (struct ip_mc_list*,int,scalar_t__*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sf_markstate (struct ip_mc_list*) ; 
 scalar_t__ sf_setstate (struct ip_mc_list*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip_mc_add_src(struct in_device *in_dev, __be32 *pmca, int sfmode,
			 int sfcount, __be32 *psfsrc, int delta)
{
	struct ip_mc_list *pmc;
	int	isexclude;
	int	i, err;

	if (!in_dev)
		return -ENODEV;
	read_lock(&in_dev->mc_list_lock);
	for (pmc=in_dev->mc_list; pmc; pmc=pmc->next) {
		if (*pmca == pmc->multiaddr)
			break;
	}
	if (!pmc) {
		/* MCA not found?? bug */
		read_unlock(&in_dev->mc_list_lock);
		return -ESRCH;
	}
	spin_lock_bh(&pmc->lock);
	read_unlock(&in_dev->mc_list_lock);

#ifdef CONFIG_IP_MULTICAST
	sf_markstate(pmc);
#endif
	isexclude = pmc->sfmode == MCAST_EXCLUDE;
	if (!delta)
		pmc->sfcount[sfmode]++;
	err = 0;
	for (i=0; i<sfcount; i++) {
		err = ip_mc_add1_src(pmc, sfmode, &psfsrc[i], delta);
		if (err)
			break;
	}
	if (err) {
		int j;

		pmc->sfcount[sfmode]--;
		for (j=0; j<i; j++)
			(void) ip_mc_del1_src(pmc, sfmode, &psfsrc[i]);
	} else if (isexclude != (pmc->sfcount[MCAST_EXCLUDE] != 0)) {
#ifdef CONFIG_IP_MULTICAST
		struct ip_sf_list *psf;
		in_dev = pmc->interface;
#endif

		/* filter mode change */
		if (pmc->sfcount[MCAST_EXCLUDE])
			pmc->sfmode = MCAST_EXCLUDE;
		else if (pmc->sfcount[MCAST_INCLUDE])
			pmc->sfmode = MCAST_INCLUDE;
#ifdef CONFIG_IP_MULTICAST
		/* else no filters; keep old mode for reports */

		pmc->crcount = in_dev->mr_qrv ? in_dev->mr_qrv :
			IGMP_Unsolicited_Report_Count;
		in_dev->mr_ifc_count = pmc->crcount;
		for (psf=pmc->sources; psf; psf = psf->sf_next)
			psf->sf_crcount = 0;
		igmp_ifc_event(in_dev);
	} else if (sf_setstate(pmc)) {
		igmp_ifc_event(in_dev);
#endif
	}
	spin_unlock_bh(&pmc->lock);
	return err;
}