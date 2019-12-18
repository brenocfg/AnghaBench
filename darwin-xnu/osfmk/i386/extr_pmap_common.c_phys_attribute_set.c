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
typedef  scalar_t__ ppnum_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MANAGED_PAGE (int) ; 
 int /*<<< orphan*/  LOCK_PVH (int) ; 
 int /*<<< orphan*/  UNLOCK_PVH (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_intr_assert () ; 
 int* pmap_phys_attributes ; 
 int ppn_to_pai (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 

void
phys_attribute_set(
	ppnum_t		pn,
	int		bits)
{
	int		pai;

	pmap_intr_assert();
	assert(pn != vm_page_fictitious_addr);
	if (pn == vm_page_guard_addr)
		return;

	pai = ppn_to_pai(pn);

	if (!IS_MANAGED_PAGE(pai)) {
		/* Not a managed page.  */
		return;
	}

	LOCK_PVH(pai);
	pmap_phys_attributes[pai] |= bits;
	UNLOCK_PVH(pai);
}