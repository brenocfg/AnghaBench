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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct tlb_args {unsigned long ta_start; unsigned long ta_end; struct vm_area_struct* ta_vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipi_flush_tlb_range ; 
 int /*<<< orphan*/  local_flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mm_cpumask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_each_cpu_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tlb_args*,int) ; 
 scalar_t__ tlb_ops_need_broadcast () ; 

void flush_tlb_range(struct vm_area_struct *vma,
                     unsigned long start, unsigned long end)
{
	if (tlb_ops_need_broadcast()) {
		struct tlb_args ta;
		ta.ta_vma = vma;
		ta.ta_start = start;
		ta.ta_end = end;
		on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_flush_tlb_range,
					&ta, 1);
	} else
		local_flush_tlb_range(vma, start, end);
}