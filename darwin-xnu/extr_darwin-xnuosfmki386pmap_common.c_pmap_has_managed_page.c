#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ppnum_t ;
struct TYPE_3__ {scalar_t__ ksize; scalar_t__ kaddr; } ;
typedef  TYPE_1__ boot_args ;
typedef  int boolean_t ;
struct TYPE_4__ {scalar_t__ bootArgs; } ;

/* Variables and functions */
 int FALSE ; 
 TYPE_2__ PE_state ; 
 int PHYS_MANAGED ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t atop_32 (scalar_t__) ; 
 size_t last_managed_page ; 
 int* pmap_phys_attributes ; 

boolean_t 
pmap_has_managed_page(ppnum_t first, ppnum_t last)
{
	ppnum_t     pn, kdata_start, kdata_end;
	boolean_t   result;
	boot_args * args;

	args        = (boot_args *) PE_state.bootArgs;

	// Allow pages that the booter added to the end of the kernel.
	// We may miss reporting some pages in this range that were freed
	// with ml_static_free()
	kdata_start = atop_32(args->kaddr);
	kdata_end   = atop_32(args->kaddr + args->ksize);

    assert(last_managed_page);
    assert(first <= last);

    for (result = FALSE, pn = first; 
    	!result 
    	  && (pn <= last)
    	  && (pn <= last_managed_page); 
    	 pn++)
    {
		if ((pn >= kdata_start) && (pn < kdata_end)) continue;
    	result = (0 != (pmap_phys_attributes[pn] & PHYS_MANAGED));
    }

	return (result);
}