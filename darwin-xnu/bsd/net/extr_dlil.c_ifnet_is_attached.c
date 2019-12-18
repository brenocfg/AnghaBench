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
struct ifnet {int /*<<< orphan*/  if_ref_lock; int /*<<< orphan*/  if_refio; } ;

/* Variables and functions */
 int IF_FULLY_ATTACHED (struct ifnet*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

int
ifnet_is_attached(struct ifnet *ifp, int refio)
{
	int ret;

	lck_mtx_lock_spin(&ifp->if_ref_lock);
	if ((ret = IF_FULLY_ATTACHED(ifp))) {
		if (refio > 0)
			ifp->if_refio++;
	}
	lck_mtx_unlock(&ifp->if_ref_lock);

	return (ret);
}