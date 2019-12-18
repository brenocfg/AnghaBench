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
typedef  int vm_offset_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pmap_paddr_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ pmap_find_phys (int /*<<< orphan*/ ,int) ; 

pmap_paddr_t
kdp_vtophys(
	pmap_t pmap,
	vm_offset_t va)
{
	pmap_paddr_t    pa;
	ppnum_t pp;

	pp = pmap_find_phys(pmap, va);
	if(!pp) return 0;
        
	pa = ((pmap_paddr_t)pp << PAGE_SHIFT) | (va & PAGE_MASK);

	return(pa);
}