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
typedef  int /*<<< orphan*/  ppnum_t ;

/* Variables and functions */
 scalar_t__ IS_MANAGED_PAGE (int) ; 
 int /*<<< orphan*/  LOCK_PVH (int) ; 
 int PHYS_NOENCRYPT ; 
 int /*<<< orphan*/  UNLOCK_PVH (int) ; 
 int* pmap_phys_attributes ; 
 int ppn_to_pai (int /*<<< orphan*/ ) ; 

void
pmap_clear_noencrypt(ppnum_t pn)
{
	int		pai;

	pai = ppn_to_pai(pn);

	if (IS_MANAGED_PAGE(pai)) {
		/*
		 * synchronization at VM layer prevents PHYS_NOENCRYPT
		 * from changing state, so we don't need the lock to inspect
		 */
		if (pmap_phys_attributes[pai] & PHYS_NOENCRYPT) {
			LOCK_PVH(pai);

			pmap_phys_attributes[pai] &= ~PHYS_NOENCRYPT;

			UNLOCK_PVH(pai);
		}
	}
}