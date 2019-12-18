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
struct pfi_kif {int /*<<< orphan*/ * pfik_ifp; } ;
struct ifnet {int /*<<< orphan*/ * if_pf_kif; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  PFI_KIF_REF_NONE ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfi_kif_unref (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfi_kif_update (struct pfi_kif*) ; 
 int /*<<< orphan*/  pfi_update ; 

void
pfi_detach_ifnet(struct ifnet *ifp)
{
	struct pfi_kif		*kif;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if ((kif = (struct pfi_kif *)ifp->if_pf_kif) == NULL)
		return;

	pfi_update++;
	pfi_kif_update(kif);

	ifnet_lock_exclusive(ifp);
	kif->pfik_ifp = NULL;
	ifp->if_pf_kif = NULL;
	ifnet_lock_done(ifp);

	pfi_kif_unref(kif, PFI_KIF_REF_NONE);
}