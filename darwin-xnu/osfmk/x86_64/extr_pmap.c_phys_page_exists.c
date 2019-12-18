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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IS_MANAGED_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_initialized ; 
 int /*<<< orphan*/  ppn_to_pai (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 

boolean_t
phys_page_exists(ppnum_t pn)
{
	assert(pn != vm_page_fictitious_addr);

	if (!pmap_initialized)
		return TRUE;

	if (pn == vm_page_guard_addr)
		return FALSE;

	if (!IS_MANAGED_PAGE(ppn_to_pai(pn)))
		return FALSE;

	return TRUE;
}