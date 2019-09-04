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
typedef  int pp_attr_t ;
typedef  scalar_t__ pmap_paddr_t ;

/* Variables and functions */
 int PP_ATTR_WIMG_MASK ; 
 unsigned int VM_WIMG_DEFAULT ; 
 unsigned int VM_WIMG_IO ; 
 scalar_t__ gPhysBase ; 
 scalar_t__ gPhysSize ; 
 scalar_t__ io_rgn_end ; 
 scalar_t__ io_rgn_start ; 
 scalar_t__ pa_index (scalar_t__) ; 
 int /*<<< orphan*/  pa_valid (scalar_t__) ; 
 unsigned int pmap_find_io_attr (scalar_t__) ; 
 int /*<<< orphan*/  pmap_initialized ; 
 int* pp_attr_table ; 
 scalar_t__ ptoa (int /*<<< orphan*/ ) ; 

unsigned int
pmap_cache_attributes(
	ppnum_t pn)
{
	pmap_paddr_t    paddr;
	int		pai;
	unsigned int	result;
	pp_attr_t	pp_attr_current;

	paddr = ptoa(pn);

	if ((paddr >= io_rgn_start) && (paddr < io_rgn_end))
		return pmap_find_io_attr(paddr);

	if (!pmap_initialized) {
		if  ((paddr >= gPhysBase) && (paddr < gPhysBase+gPhysSize))
			return (VM_WIMG_DEFAULT);
		else
			return (VM_WIMG_IO);
	}


	if (!pa_valid(paddr))
		return (VM_WIMG_IO);

	result = VM_WIMG_DEFAULT;

	pai = (int)pa_index(paddr);

	pp_attr_current = pp_attr_table[pai];
	if (pp_attr_current & PP_ATTR_WIMG_MASK)
		result = pp_attr_current & PP_ATTR_WIMG_MASK;
	return result;
}