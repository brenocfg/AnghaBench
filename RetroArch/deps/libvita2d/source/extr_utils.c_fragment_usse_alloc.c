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
typedef  int /*<<< orphan*/  SceUID ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE ; 
 scalar_t__ sceGxmMapFragmentUsseMemory (void*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  sceKernelAllocMemBlock (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ sceKernelGetMemBlockBase (int /*<<< orphan*/ ,void**) ; 

void *fragment_usse_alloc(unsigned int size, SceUID *uid, unsigned int *usse_offset)
{
	void *mem = NULL;

	size = ALIGN(size, 4096);
	*uid = sceKernelAllocMemBlock("fragment_usse", SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE, size, NULL);

	if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
		return NULL;
	if (sceGxmMapFragmentUsseMemory(mem, size, usse_offset) < 0)
		return NULL;

	return mem;
}