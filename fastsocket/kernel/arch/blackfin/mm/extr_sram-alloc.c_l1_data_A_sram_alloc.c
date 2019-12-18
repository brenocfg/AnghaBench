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

/* Variables and functions */
 void* _sram_alloc (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_l1_data_A_sram_head ; 
 unsigned int get_cpu () ; 
 int /*<<< orphan*/  l1_data_sram_lock ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,size_t) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  used_l1_data_A_sram_head ; 

void *l1_data_A_sram_alloc(size_t size)
{
#if L1_DATA_A_LENGTH != 0
	unsigned long flags;
	void *addr;
	unsigned int cpu;

	cpu = get_cpu();
	/* add mutex operation */
	spin_lock_irqsave(&per_cpu(l1_data_sram_lock, cpu), flags);

	addr = _sram_alloc(size, &per_cpu(free_l1_data_A_sram_head, cpu),
			&per_cpu(used_l1_data_A_sram_head, cpu));

	/* add mutex operation */
	spin_unlock_irqrestore(&per_cpu(l1_data_sram_lock, cpu), flags);
	put_cpu();

	pr_debug("Allocated address in l1_data_A_sram_alloc is 0x%lx+0x%lx\n",
		 (long unsigned int)addr, size);

	return addr;
#else
	return NULL;
#endif
}