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
 int /*<<< orphan*/  free_l2_sram_head ; 
 int /*<<< orphan*/  l2_sram_lock ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  used_l2_sram_head ; 

void *l2_sram_alloc(size_t size)
{
#if L2_LENGTH != 0
	unsigned long flags;
	void *addr;

	/* add mutex operation */
	spin_lock_irqsave(&l2_sram_lock, flags);

	addr = _sram_alloc(size, &free_l2_sram_head,
			&used_l2_sram_head);

	/* add mutex operation */
	spin_unlock_irqrestore(&l2_sram_lock, flags);

	pr_debug("Allocated address in l2_sram_alloc is 0x%lx+0x%lx\n",
		 (long unsigned int)addr, size);

	return addr;
#else
	return NULL;
#endif
}