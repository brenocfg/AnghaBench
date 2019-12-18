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
struct TYPE_4__ {int /*<<< orphan*/  pan_offset; scalar_t__ pan_display; } ;
struct intelfb_info {TYPE_1__* pdev; int /*<<< orphan*/  int_lock; TYPE_2__ vsync; int /*<<< orphan*/  irq_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSPABASE ; 
 int /*<<< orphan*/  HWSTAM ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IIR ; 
 int /*<<< orphan*/  IMR ; 
 int INREG16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct intelfb_info*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void intelfbhw_disable_irq(struct intelfb_info *dinfo)
{
	if (test_and_clear_bit(0, &dinfo->irq_flags)) {
		if (dinfo->vsync.pan_display) {
			dinfo->vsync.pan_display = 0;
			OUTREG(DSPABASE, dinfo->vsync.pan_offset);
		}
		spin_lock_irq(&dinfo->int_lock);
		OUTREG16(HWSTAM, 0xffff);
		OUTREG16(IMR, 0xffff);
		OUTREG16(IER, 0x0);

		OUTREG16(IIR, INREG16(IIR)); /* clear IRQ requests */
		spin_unlock_irq(&dinfo->int_lock);

		free_irq(dinfo->pdev->irq, dinfo);
	}
}