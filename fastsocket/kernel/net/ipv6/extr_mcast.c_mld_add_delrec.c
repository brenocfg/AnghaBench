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
struct ip6_sf_list {int /*<<< orphan*/  sf_crcount; struct ip6_sf_list* sf_next; } ;
struct inet6_dev {int /*<<< orphan*/  mc_lock; struct ifmcaddr6* mc_tomb; int /*<<< orphan*/  mc_qrv; } ;
struct ifmcaddr6 {scalar_t__ mca_sfmode; struct ifmcaddr6* next; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_crcount; struct ip6_sf_list* mca_sources; int /*<<< orphan*/  mca_tomb; int /*<<< orphan*/  mca_addr; int /*<<< orphan*/  idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MCAST_INCLUDE ; 
 int /*<<< orphan*/  in6_dev_hold (struct inet6_dev*) ; 
 struct ifmcaddr6* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mld_add_delrec(struct inet6_dev *idev, struct ifmcaddr6 *im)
{
	struct ifmcaddr6 *pmc;

	/* this is an "ifmcaddr6" for convenience; only the fields below
	 * are actually used. In particular, the refcnt and users are not
	 * used for management of the delete list. Using the same structure
	 * for deleted items allows change reports to use common code with
	 * non-deleted or query-response MCA's.
	 */
	pmc = kzalloc(sizeof(*pmc), GFP_ATOMIC);
	if (!pmc)
		return;

	spin_lock_bh(&im->mca_lock);
	spin_lock_init(&pmc->mca_lock);
	pmc->idev = im->idev;
	in6_dev_hold(idev);
	pmc->mca_addr = im->mca_addr;
	pmc->mca_crcount = idev->mc_qrv;
	pmc->mca_sfmode = im->mca_sfmode;
	if (pmc->mca_sfmode == MCAST_INCLUDE) {
		struct ip6_sf_list *psf;

		pmc->mca_tomb = im->mca_tomb;
		pmc->mca_sources = im->mca_sources;
		im->mca_tomb = im->mca_sources = NULL;
		for (psf=pmc->mca_sources; psf; psf=psf->sf_next)
			psf->sf_crcount = pmc->mca_crcount;
	}
	spin_unlock_bh(&im->mca_lock);

	write_lock_bh(&idev->mc_lock);
	pmc->next = idev->mc_tomb;
	idev->mc_tomb = pmc;
	write_unlock_bh(&idev->mc_lock);
}