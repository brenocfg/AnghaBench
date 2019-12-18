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

/* Variables and functions */
 unsigned long PCI64_ATTR_PREF ; 
 int PCI64_ATTR_TARG_SHFT ; 
 unsigned long TO_PHYS_MASK ; 
 unsigned long virt_to_bus (void*) ; 

__attribute__((used)) static inline unsigned long ioc3_map(void *ptr, unsigned long vdev)
{
#ifdef CONFIG_SGI_IP27
	vdev <<= 57;   /* Shift to PCI64_ATTR_VIRTUAL */

	return vdev | (0xaUL << PCI64_ATTR_TARG_SHFT) | PCI64_ATTR_PREF |
	       ((unsigned long)ptr & TO_PHYS_MASK);
#else
	return virt_to_bus(ptr);
#endif
}