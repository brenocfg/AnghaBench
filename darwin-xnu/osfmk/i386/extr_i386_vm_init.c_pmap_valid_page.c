#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ppnum_t ;
struct TYPE_3__ {scalar_t__ base; scalar_t__ end; } ;
typedef  TYPE_1__ pmap_memory_region_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int pmap_memory_region_count ; 
 TYPE_1__* pmap_memory_regions ; 

boolean_t
pmap_valid_page(
	ppnum_t pn)
{
        unsigned int i;
	pmap_memory_region_t *pmptr = pmap_memory_regions;

	for (i = 0; i < pmap_memory_region_count; i++, pmptr++) {
	        if ( (pn >= pmptr->base) && (pn <= pmptr->end) )
	                return TRUE;
	}
	return FALSE;
}