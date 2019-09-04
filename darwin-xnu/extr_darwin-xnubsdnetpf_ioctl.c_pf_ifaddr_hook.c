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
struct pfi_kif {int dummy; } ;
struct ifnet {struct pfi_kif* if_pf_kif; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pf_perim_lock ; 
 int /*<<< orphan*/  pfi_kifaddr_update (struct pfi_kif*) ; 

int
pf_ifaddr_hook(struct ifnet *ifp)
{
	struct pfi_kif *kif = ifp->if_pf_kif;

	if (kif != NULL) {
		lck_rw_lock_shared(pf_perim_lock);
		lck_mtx_lock(pf_lock);

		pfi_kifaddr_update(kif);

		lck_mtx_unlock(pf_lock);
		lck_rw_done(pf_perim_lock);
	}
	return (0);
}