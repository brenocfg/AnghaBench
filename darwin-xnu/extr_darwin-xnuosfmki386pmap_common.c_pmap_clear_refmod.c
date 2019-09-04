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
 unsigned int PHYS_MODIFIED ; 
 unsigned int PHYS_REFERENCED ; 
 unsigned int VM_MEM_MODIFIED ; 
 unsigned int VM_MEM_REFERENCED ; 
 int /*<<< orphan*/  phys_attribute_clear (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
pmap_clear_refmod(ppnum_t pn, unsigned int mask)
{
	unsigned int  x86Mask;

	x86Mask = (   ((mask &   VM_MEM_MODIFIED)?   PHYS_MODIFIED : 0)
	            | ((mask & VM_MEM_REFERENCED)? PHYS_REFERENCED : 0));

	phys_attribute_clear(pn, x86Mask, 0, NULL);
}