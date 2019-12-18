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
struct vm_area_struct {int /*<<< orphan*/ * vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __local_flush_tlb_page (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_get_tsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_virtual_psize ; 

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long vmaddr)
{
	__local_flush_tlb_page(vma ? vma->vm_mm : NULL, vmaddr,
			       mmu_get_tsize(mmu_virtual_psize), 0);
}