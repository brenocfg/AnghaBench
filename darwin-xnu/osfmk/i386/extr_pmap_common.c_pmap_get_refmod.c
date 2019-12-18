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
 int PHYS_MODIFIED ; 
 int PHYS_REFERENCED ; 
 unsigned int VM_MEM_MODIFIED ; 
 unsigned int VM_MEM_REFERENCED ; 
 int phys_attribute_test (int /*<<< orphan*/ ,int) ; 

unsigned int
pmap_get_refmod(ppnum_t pn)
{
        int		refmod;
	unsigned int	retval = 0;

	refmod = phys_attribute_test(pn, PHYS_MODIFIED | PHYS_REFERENCED);

	if (refmod & PHYS_MODIFIED)
	        retval |= VM_MEM_MODIFIED;
	if (refmod & PHYS_REFERENCED)
	        retval |= VM_MEM_REFERENCED;

	return (retval);
}