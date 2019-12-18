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
 int _sram_free (void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_l2_sram_head ; 
 int /*<<< orphan*/  l2_sram_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  used_l2_sram_head ; 

int l2_sram_free(const void *addr)
{
#if L2_LENGTH != 0
	unsigned long flags;
	int ret;

	/* add mutex operation */
	spin_lock_irqsave(&l2_sram_lock, flags);

	ret = _sram_free(addr, &free_l2_sram_head,
			&used_l2_sram_head);

	/* add mutex operation */
	spin_unlock_irqrestore(&l2_sram_lock, flags);

	return ret;
#else
	return -1;
#endif
}