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
struct vm_struct {int dummy; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MODULES_END ; 
 unsigned long MODULES_LEN ; 
 int /*<<< orphan*/  MODULES_VADDR ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_KERNEL_EXEC ; 
 int /*<<< orphan*/  VM_ALLOC ; 
 int __GFP_HIGHMEM ; 
 struct vm_struct* __get_vm_area (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* __vmalloc_area (struct vm_struct*,int,int /*<<< orphan*/ ) ; 

void *module_alloc(unsigned long size)
{
	struct vm_struct *area;

	if (!size)
		return NULL;
	size = PAGE_ALIGN(size);
	if (size > MODULES_LEN)
		return NULL;

	area = __get_vm_area(size, VM_ALLOC, MODULES_VADDR, MODULES_END);
	if (!area)
		return NULL;

	return __vmalloc_area(area, GFP_KERNEL | __GFP_HIGHMEM,
					PAGE_KERNEL_EXEC);
}