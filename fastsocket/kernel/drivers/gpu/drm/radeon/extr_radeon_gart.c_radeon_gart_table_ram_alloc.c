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
struct TYPE_2__ {int table_size; void* ptr; int /*<<< orphan*/  table_addr; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ gart; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ CHIP_RS400 ; 
 scalar_t__ CHIP_RS480 ; 
 scalar_t__ CHIP_RS690 ; 
 scalar_t__ CHIP_RS740 ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_memory_uc (unsigned long,int) ; 

int radeon_gart_table_ram_alloc(struct radeon_device *rdev)
{
	void *ptr;

	ptr = pci_alloc_consistent(rdev->pdev, rdev->gart.table_size,
				   &rdev->gart.table_addr);
	if (ptr == NULL) {
		return -ENOMEM;
	}
#ifdef CONFIG_X86
	if (rdev->family == CHIP_RS400 || rdev->family == CHIP_RS480 ||
	    rdev->family == CHIP_RS690 || rdev->family == CHIP_RS740) {
		set_memory_uc((unsigned long)ptr,
			      rdev->gart.table_size >> PAGE_SHIFT);
	}
#endif
	rdev->gart.ptr = ptr;
	memset((void *)rdev->gart.ptr, 0, rdev->gart.table_size);
	return 0;
}