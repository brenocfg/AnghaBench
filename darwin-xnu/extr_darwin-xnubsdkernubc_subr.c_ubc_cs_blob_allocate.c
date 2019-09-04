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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_SECURITY ; 
 scalar_t__ kalloc_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
ubc_cs_blob_allocate(
	vm_offset_t	*blob_addr_p,
	vm_size_t	*blob_size_p)
{
	kern_return_t	kr = KERN_FAILURE;

	{
		*blob_addr_p = (vm_offset_t) kalloc_tag(*blob_size_p, VM_KERN_MEMORY_SECURITY);

		if (*blob_addr_p == 0) {
			kr = KERN_NO_SPACE;
		} else {
			kr = KERN_SUCCESS;
		}
	}

	return kr;
}