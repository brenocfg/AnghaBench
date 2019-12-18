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
 int /*<<< orphan*/  FALSE ; 
 int INTEL_PTE_NCACHE ; 
 unsigned int VM_WIMG_COPYBACK ; 
 unsigned int VM_WIMG_IO ; 
 int pmap_get_cache_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int pmap_cache_attributes(ppnum_t pn) {
	if (pmap_get_cache_attributes(pn, FALSE) & INTEL_PTE_NCACHE)
	        return (VM_WIMG_IO);
	else
		return (VM_WIMG_COPYBACK);
}