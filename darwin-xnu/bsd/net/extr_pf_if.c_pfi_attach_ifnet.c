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
struct pfi_kif {struct ifnet* pfik_ifp; } ;
struct ifnet {struct pfi_kif* if_pf_kif; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pf_lock ; 
 struct pfi_kif* pfi_kif_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfi_kif_update (struct pfi_kif*) ; 
 int /*<<< orphan*/  pfi_update ; 

void
pfi_attach_ifnet(struct ifnet *ifp)
{
	struct pfi_kif *kif;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	pfi_update++;
	if ((kif = pfi_kif_get(if_name(ifp))) == NULL)
		panic("pfi_kif_get failed");

	ifnet_lock_exclusive(ifp);
	kif->pfik_ifp = ifp;
	ifp->if_pf_kif = kif;
	ifnet_lock_done(ifp);

	pfi_kif_update(kif);
}