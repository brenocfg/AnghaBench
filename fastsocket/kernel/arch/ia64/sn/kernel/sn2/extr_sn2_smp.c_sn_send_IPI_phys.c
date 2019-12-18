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
 scalar_t__ GLOBAL_MMR_PHYS_ADDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH_IPI_INT ; 
 int SH_IPI_INT_BASE_SHFT ; 
 long SH_IPI_INT_IDX_SHFT ; 
 long SH_IPI_INT_PID_SHFT ; 
 unsigned long SH_IPI_INT_SEND_SHFT ; 
 long SH_IPI_INT_TYPE_SHFT ; 
 scalar_t__ enable_shub_wars_1_1 () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pio_phys_write_mmr (long volatile*,long) ; 
 int /*<<< orphan*/  sn2_global_ptc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_piowc () ; 

void sn_send_IPI_phys(int nasid, long physid, int vector, int delivery_mode)
{
	long val;
	unsigned long flags = 0;
	volatile long *p;

	p = (long *)GLOBAL_MMR_PHYS_ADDR(nasid, SH_IPI_INT);
	val = (1UL << SH_IPI_INT_SEND_SHFT) |
	    (physid << SH_IPI_INT_PID_SHFT) |
	    ((long)delivery_mode << SH_IPI_INT_TYPE_SHFT) |
	    ((long)vector << SH_IPI_INT_IDX_SHFT) |
	    (0x000feeUL << SH_IPI_INT_BASE_SHFT);

	mb();
	if (enable_shub_wars_1_1()) {
		spin_lock_irqsave(&sn2_global_ptc_lock, flags);
	}
	pio_phys_write_mmr(p, val);
	if (enable_shub_wars_1_1()) {
		wait_piowc();
		spin_unlock_irqrestore(&sn2_global_ptc_lock, flags);
	}

}