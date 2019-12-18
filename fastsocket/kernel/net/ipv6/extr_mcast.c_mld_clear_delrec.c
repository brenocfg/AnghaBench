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
struct ip6_sf_list {struct ip6_sf_list* sf_next; int /*<<< orphan*/  mca_lock; struct ip6_sf_list* mca_tomb; struct ip6_sf_list* next; int /*<<< orphan*/  idev; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct ip6_sf_list* mc_list; int /*<<< orphan*/  mc_lock; struct ip6_sf_list* mc_tomb; } ;
struct ifmcaddr6 {struct ifmcaddr6* sf_next; int /*<<< orphan*/  mca_lock; struct ifmcaddr6* mca_tomb; struct ifmcaddr6* next; int /*<<< orphan*/  idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  in6_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_mc_clear_src (struct ip6_sf_list*) ; 
 int /*<<< orphan*/  kfree (struct ip6_sf_list*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mld_clear_delrec(struct inet6_dev *idev)
{
	struct ifmcaddr6 *pmc, *nextpmc;

	write_lock_bh(&idev->mc_lock);
	pmc = idev->mc_tomb;
	idev->mc_tomb = NULL;
	write_unlock_bh(&idev->mc_lock);

	for (; pmc; pmc = nextpmc) {
		nextpmc = pmc->next;
		ip6_mc_clear_src(pmc);
		in6_dev_put(pmc->idev);
		kfree(pmc);
	}

	/* clear dead sources, too */
	read_lock_bh(&idev->lock);
	for (pmc=idev->mc_list; pmc; pmc=pmc->next) {
		struct ip6_sf_list *psf, *psf_next;

		spin_lock_bh(&pmc->mca_lock);
		psf = pmc->mca_tomb;
		pmc->mca_tomb = NULL;
		spin_unlock_bh(&pmc->mca_lock);
		for (; psf; psf=psf_next) {
			psf_next = psf->sf_next;
			kfree(psf);
		}
	}
	read_unlock_bh(&idev->lock);
}