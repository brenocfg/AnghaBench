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
struct TYPE_2__ {unsigned long ptce_base; unsigned long* ptce_count; unsigned long* ptce_stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_ptce (unsigned long) ; 
 int /*<<< orphan*/  ia64_srlz_i () ; 
 TYPE_1__* local_cpu_data ; 
 int /*<<< orphan*/  local_irq_restore (long) ; 
 int /*<<< orphan*/  local_irq_save (long) ; 

__attribute__((used)) static void kvm_flush_tlb_all(void)
{
	unsigned long i, j, count0, count1, stride0, stride1, addr;
	long flags;

	addr    = local_cpu_data->ptce_base;
	count0  = local_cpu_data->ptce_count[0];
	count1  = local_cpu_data->ptce_count[1];
	stride0 = local_cpu_data->ptce_stride[0];
	stride1 = local_cpu_data->ptce_stride[1];

	local_irq_save(flags);
	for (i = 0; i < count0; ++i) {
		for (j = 0; j < count1; ++j) {
			ia64_ptce(addr);
			addr += stride1;
		}
		addr += stride0;
	}
	local_irq_restore(flags);
	ia64_srlz_i();			/* srlz.i implies srlz.d */
}