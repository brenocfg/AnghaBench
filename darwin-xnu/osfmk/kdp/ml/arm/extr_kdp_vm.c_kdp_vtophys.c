#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  scalar_t__ ppnum_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int pmap_paddr_t ;
struct TYPE_5__ {int min; int max; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 TYPE_1__* kernel_pmap ; 
 scalar_t__ pmap_find_phys (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned long,unsigned int,unsigned int) ; 

pmap_paddr_t
kdp_vtophys(
	    pmap_t pmap,
	    vm_offset_t va)
{
	pmap_paddr_t    pa;
	ppnum_t         pp;

	/* Ensure that the provided va resides within the provided pmap range. */
	if(!pmap || ((pmap != kernel_pmap) && ((va < pmap->min) || (va >= pmap->max))))
	{
#ifdef KDP_VTOPHYS_DEBUG
		printf("kdp_vtophys(%08x, %016lx) not in range %08x .. %08x\n", (unsigned int) pmap,
		                                                                (unsigned long) va,
		                                                                (unsigned int) (pmap ? pmap->min : 0),
		                                                                (unsigned int) (pmap ? pmap->max : 0));
#endif
		return 0;   /* Just return if no translation */	
	}

	pp = pmap_find_phys(pmap, va);	/* Get the page number */
	if (!pp)
		return 0;	/* Just return if no translation */

	pa = ((pmap_paddr_t) pp << PAGE_SHIFT) | (va & PAGE_MASK);	/* Insert page offset */
	return (pa);
}