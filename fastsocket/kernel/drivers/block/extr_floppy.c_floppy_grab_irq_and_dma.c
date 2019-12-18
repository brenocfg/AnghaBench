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
struct TYPE_2__ {int address; int /*<<< orphan*/  dor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  FD_DOR ; 
 int /*<<< orphan*/  FLOPPY_DMA ; 
 int /*<<< orphan*/  FLOPPY_IRQ ; 
 scalar_t__ N_FDC ; 
 int can_use_virtual_dma ; 
 int /*<<< orphan*/  fd_free_dma () ; 
 int /*<<< orphan*/  fd_free_irq () ; 
 int /*<<< orphan*/  fd_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fd_request_dma () ; 
 scalar_t__ fd_request_irq () ; 
 scalar_t__ fdc ; 
 int /*<<< orphan*/  floppy_release_regions (scalar_t__) ; 
 scalar_t__ floppy_request_regions (scalar_t__) ; 
 int /*<<< orphan*/  floppy_usage_lock ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int irqdma_allocated ; 
 int /*<<< orphan*/  reset_fdc_info (int) ; 
 int /*<<< orphan*/  set_dor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usage_count ; 
 int use_virtual_dma ; 

__attribute__((used)) static int floppy_grab_irq_and_dma(void)
{
	unsigned long flags;

	spin_lock_irqsave(&floppy_usage_lock, flags);
	if (usage_count++) {
		spin_unlock_irqrestore(&floppy_usage_lock, flags);
		return 0;
	}
	spin_unlock_irqrestore(&floppy_usage_lock, flags);

	/*
	 * We might have scheduled a free_irq(), wait it to
	 * drain first:
	 */
	flush_scheduled_work();

	if (fd_request_irq()) {
		DPRINT("Unable to grab IRQ%d for the floppy driver\n",
		       FLOPPY_IRQ);
		spin_lock_irqsave(&floppy_usage_lock, flags);
		usage_count--;
		spin_unlock_irqrestore(&floppy_usage_lock, flags);
		return -1;
	}
	if (fd_request_dma()) {
		DPRINT("Unable to grab DMA%d for the floppy driver\n",
		       FLOPPY_DMA);
		if (can_use_virtual_dma & 2)
			use_virtual_dma = can_use_virtual_dma = 1;
		if (!(can_use_virtual_dma & 1)) {
			fd_free_irq();
			spin_lock_irqsave(&floppy_usage_lock, flags);
			usage_count--;
			spin_unlock_irqrestore(&floppy_usage_lock, flags);
			return -1;
		}
	}

	for (fdc = 0; fdc < N_FDC; fdc++) {
		if (FDCS->address != -1) {
			if (floppy_request_regions(fdc))
				goto cleanup;
		}
	}
	for (fdc = 0; fdc < N_FDC; fdc++) {
		if (FDCS->address != -1) {
			reset_fdc_info(1);
			fd_outb(FDCS->dor, FD_DOR);
		}
	}
	fdc = 0;
	set_dor(0, ~0, 8);	/* avoid immediate interrupt */

	for (fdc = 0; fdc < N_FDC; fdc++)
		if (FDCS->address != -1)
			fd_outb(FDCS->dor, FD_DOR);
	/*
	 * The driver will try and free resources and relies on us
	 * to know if they were allocated or not.
	 */
	fdc = 0;
	irqdma_allocated = 1;
	return 0;
cleanup:
	fd_free_irq();
	fd_free_dma();
	while (--fdc >= 0)
		floppy_release_regions(fdc);
	spin_lock_irqsave(&floppy_usage_lock, flags);
	usage_count--;
	spin_unlock_irqrestore(&floppy_usage_lock, flags);
	return -1;
}