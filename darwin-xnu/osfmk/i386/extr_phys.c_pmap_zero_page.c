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
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i386_ptob (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 
 scalar_t__ vm_page_guard_addr ; 

void
pmap_zero_page(
       ppnum_t pn)
{
	assert(pn != vm_page_fictitious_addr);
	assert(pn != vm_page_guard_addr);
	bzero_phys((addr64_t)i386_ptob(pn), PAGE_SIZE);
}