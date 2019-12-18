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
typedef  int /*<<< orphan*/  vm_tag_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KMEM_ALLOC_CODE ; 
 int /*<<< orphan*/  KMEM_ALLOC_CODE_2 ; 
 int /*<<< orphan*/  TRACE_MACHLEAKS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_memory_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

kern_return_t
kmem_alloc_flags(
	vm_map_t	map,
	vm_offset_t	*addrp,
	vm_size_t	size,
	vm_tag_t 	tag,
	int 		flags)
{
	kern_return_t kr = kernel_memory_allocate(map, addrp, size, 0, flags, tag);
	TRACE_MACHLEAKS(KMEM_ALLOC_CODE, KMEM_ALLOC_CODE_2, size, *addrp);
	return kr;
}