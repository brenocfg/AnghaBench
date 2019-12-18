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
typedef  int /*<<< orphan*/  pv_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  scalar_t__ pmap_paddr_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PVH_TYPE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pa_index (scalar_t__) ; 
 int /*<<< orphan*/  pa_valid (scalar_t__) ; 
 int /*<<< orphan*/ ** pai_to_pvh (int) ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_test_type (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_fictitious_addr ; 

boolean_t
pmap_verify_free(
	ppnum_t ppnum)
{
	pv_entry_t		**pv_h;
	int             pai;
	pmap_paddr_t    phys = ptoa(ppnum);

	assert(phys != vm_page_fictitious_addr);

	if (!pa_valid(phys))
		return (FALSE);

	pai = (int)pa_index(phys);
	pv_h = pai_to_pvh(pai);

	return (pvh_test_type(pv_h, PVH_TYPE_NULL));
}