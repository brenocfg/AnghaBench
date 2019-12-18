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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/ * typefilter_t ;

/* Variables and functions */
 size_t KDBG_TYPEFILTER_BITMAP_SIZE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TYPEFILTER_ALLOC_SIZE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_DIAG ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static typefilter_t typefilter_create(void)
{
	typefilter_t tf;
	if (KERN_SUCCESS == kmem_alloc(kernel_map, (vm_offset_t*)&tf, TYPEFILTER_ALLOC_SIZE, VM_KERN_MEMORY_DIAG)) {
		memset(&tf[KDBG_TYPEFILTER_BITMAP_SIZE], 0, TYPEFILTER_ALLOC_SIZE - KDBG_TYPEFILTER_BITMAP_SIZE);
		return tf;
	}
	return NULL;
}