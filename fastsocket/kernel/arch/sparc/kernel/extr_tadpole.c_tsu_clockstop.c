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
 int CLOCK_INIT_DONE ; 
 unsigned int MACIO_EN_DMA ; 
 int /*<<< orphan*/  MACIO_SCSI_CSR_ADDR ; 
 int* clk_ctrl ; 
 int /*<<< orphan*/  clk_init () ; 
 int /*<<< orphan*/  clk_slow () ; 
 int clk_state ; 
 unsigned int ldphys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void tsu_clockstop(void)
{
	unsigned int mcsr;
	unsigned long flags;

	if (!clk_ctrl)
		return;
	if (!(clk_state & CLOCK_INIT_DONE)) {
		local_irq_save(flags);
		clk_init();
		clk_state |= CLOCK_INIT_DONE;       /* all done */
		local_irq_restore(flags);
		return;
	}
	if (!(clk_ctrl[2] & 1))
		return;               /* no speed up yet */

	local_irq_save(flags);

	/* if SCSI DMA in progress, don't slow clock */
	mcsr = ldphys(MACIO_SCSI_CSR_ADDR);
	if ((mcsr&MACIO_EN_DMA) != 0) {
		local_irq_restore(flags);
		return;
	}
	/* TODO... the minimum clock setting ought to increase the
	 * memory refresh interval..
	 */
	clk_slow();
	local_irq_restore(flags);
}