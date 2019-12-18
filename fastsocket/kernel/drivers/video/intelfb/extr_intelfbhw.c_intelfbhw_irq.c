#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  count; int /*<<< orphan*/  pan_offset; scalar_t__ pan_display; } ;
struct intelfb_info {int /*<<< orphan*/  int_lock; TYPE_3__ vsync; TYPE_2__* info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int vmode; } ;
struct TYPE_5__ {TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSPABASE ; 
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  IIR ; 
 int /*<<< orphan*/  INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INREG16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPEASTAT ; 
 int /*<<< orphan*/  PIPE_A_EVENT_INTERRUPT ; 
 int /*<<< orphan*/  VSYNC_PIPE_A_INTERRUPT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t intelfbhw_irq(int irq, void *dev_id)
{
	u16 tmp;
	struct intelfb_info *dinfo = dev_id;

	spin_lock(&dinfo->int_lock);

	tmp = INREG16(IIR);
	if (dinfo->info->var.vmode & FB_VMODE_INTERLACED)
		tmp &= PIPE_A_EVENT_INTERRUPT;
	else
		tmp &= VSYNC_PIPE_A_INTERRUPT; /* non-interlaced */

	if (tmp == 0) {
		spin_unlock(&dinfo->int_lock);
		return IRQ_RETVAL(0); /* not us */
	}

	/* clear status bits 0-15 ASAP and don't touch bits 16-31 */
	OUTREG(PIPEASTAT, INREG(PIPEASTAT));

	OUTREG16(IIR, tmp);
	if (dinfo->vsync.pan_display) {
		dinfo->vsync.pan_display = 0;
		OUTREG(DSPABASE, dinfo->vsync.pan_offset);
	}

	dinfo->vsync.count++;
	wake_up_interruptible(&dinfo->vsync.wait);

	spin_unlock(&dinfo->int_lock);

	return IRQ_RETVAL(1);
}