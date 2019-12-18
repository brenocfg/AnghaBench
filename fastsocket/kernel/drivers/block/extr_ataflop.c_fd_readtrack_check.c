#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int spt; } ;
struct TYPE_3__ {int dma_lo; int dma_md; int dma_hi; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  EXTD_DMA ; 
 int /*<<< orphan*/  FDCCMD_FORCI ; 
 int /*<<< orphan*/  FDCREG_CMD ; 
 int /*<<< orphan*/  FDC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  MFPDELAY () ; 
 scalar_t__ MultReadInProgress ; 
 int PhysTrackBuffer ; 
 int /*<<< orphan*/  SET_IRQ_HANDLER (int /*<<< orphan*/ *) ; 
 TYPE_2__* SUDT ; 
 TYPE_1__ dma_wd ; 
 int /*<<< orphan*/  fd_rwsec_done1 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  readtrack_timer ; 
 int st_dma_ext_dmahi ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void fd_readtrack_check( unsigned long dummy )
{
	unsigned long flags, addr, addr2;

	local_irq_save(flags);

	if (!MultReadInProgress) {
		/* This prevents a race condition that could arise if the
		 * interrupt is triggered while the calling of this timer
		 * callback function takes place. The IRQ function then has
		 * already cleared 'MultReadInProgress'  when flow of control
		 * gets here.
		 */
		local_irq_restore(flags);
		return;
	}

	/* get the current DMA address */
	/* ++ f.a. read twice to avoid being fooled by switcher */
	addr = 0;
	do {
		addr2 = addr;
		addr = dma_wd.dma_lo & 0xff;
		MFPDELAY();
		addr |= (dma_wd.dma_md & 0xff) << 8;
		MFPDELAY();
		if (ATARIHW_PRESENT( EXTD_DMA ))
			addr |= (st_dma_ext_dmahi & 0xffff) << 16;
		else
			addr |= (dma_wd.dma_hi & 0xff) << 16;
		MFPDELAY();
	} while(addr != addr2);
  
	if (addr >= PhysTrackBuffer + SUDT->spt*512) {
		/* already read enough data, force an FDC interrupt to stop
		 * the read operation
		 */
		SET_IRQ_HANDLER( NULL );
		MultReadInProgress = 0;
		local_irq_restore(flags);
		DPRINT(("fd_readtrack_check(): done\n"));
		FDC_WRITE( FDCREG_CMD, FDCCMD_FORCI );
		udelay(25);

		/* No error until now -- the FDC would have interrupted
		 * otherwise!
		 */
		fd_rwsec_done1(0);
	}
	else {
		/* not yet finished, wait another tenth rotation */
		local_irq_restore(flags);
		DPRINT(("fd_readtrack_check(): not yet finished\n"));
		mod_timer(&readtrack_timer, jiffies + HZ/5/10);
	}
}