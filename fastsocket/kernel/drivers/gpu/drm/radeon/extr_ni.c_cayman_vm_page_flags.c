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
typedef  int uint32_t ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int R600_ENTRY_VALID ; 
 int R600_PTE_READABLE ; 
 int R600_PTE_SNOOPED ; 
 int R600_PTE_SYSTEM ; 
 int R600_PTE_WRITEABLE ; 
 int RADEON_VM_PAGE_READABLE ; 
 int RADEON_VM_PAGE_SNOOPED ; 
 int RADEON_VM_PAGE_SYSTEM ; 
 int RADEON_VM_PAGE_VALID ; 
 int RADEON_VM_PAGE_WRITEABLE ; 

uint32_t cayman_vm_page_flags(struct radeon_device *rdev, uint32_t flags)
{
	uint32_t r600_flags = 0;
	r600_flags |= (flags & RADEON_VM_PAGE_VALID) ? R600_ENTRY_VALID : 0;
	r600_flags |= (flags & RADEON_VM_PAGE_READABLE) ? R600_PTE_READABLE : 0;
	r600_flags |= (flags & RADEON_VM_PAGE_WRITEABLE) ? R600_PTE_WRITEABLE : 0;
	if (flags & RADEON_VM_PAGE_SYSTEM) {
		r600_flags |= R600_PTE_SYSTEM;
		r600_flags |= (flags & RADEON_VM_PAGE_SNOOPED) ? R600_PTE_SNOOPED : 0;
	}
	return r600_flags;
}