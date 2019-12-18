#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  scalar_t__ pmap_paddr_t ;
struct TYPE_2__ {scalar_t__ len; scalar_t__ pa; scalar_t__ va; } ;

/* Variables and functions */
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 size_t PTOV_TABLE_SIZE ; 
 scalar_t__ gPhysBase ; 
 scalar_t__ gVirtBase ; 
 TYPE_1__* ptov_table ; 

vm_map_address_t
phystokv_range(pmap_paddr_t pa, vm_size_t *max_len)
{
	vm_size_t len;
	for (size_t i = 0; (i < PTOV_TABLE_SIZE) && (ptov_table[i].len != 0); i++) {
		if ((pa >= ptov_table[i].pa) && (pa < (ptov_table[i].pa + ptov_table[i].len))) {
			len = ptov_table[i].len - (pa - ptov_table[i].pa);
			if (*max_len > len)
				*max_len = len;
			return (pa - ptov_table[i].pa + ptov_table[i].va);
		}
	}
	len = PAGE_SIZE - (pa & PAGE_MASK);
	if (*max_len > len)
		*max_len = len;
	return (pa - gPhysBase + gVirtBase);
}