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
typedef  int /*<<< orphan*/  hp_sdc_irqhook ;
struct TYPE_2__ {int im; int set_im; int /*<<< orphan*/  task; int /*<<< orphan*/  hook_lock; int /*<<< orphan*/ * cooked; int /*<<< orphan*/ * hil; } ;

/* Variables and functions */
 int EINVAL ; 
 int HP_SDC_IM_HIL ; 
 int HP_SDC_IM_RESET ; 
 TYPE_1__ hp_sdc ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int hp_sdc_release_hil_irq(hp_sdc_irqhook *callback)
{
	write_lock_irq(&hp_sdc.hook_lock);
	if ((callback != hp_sdc.hil) ||
	    (hp_sdc.hil == NULL)) {
		write_unlock_irq(&hp_sdc.hook_lock);
		return -EINVAL;
	}

	hp_sdc.hil = NULL;
	/* Disable interrupts from HIL only if there is no cooked driver. */
	if(hp_sdc.cooked == NULL) {
		hp_sdc.im |= (HP_SDC_IM_HIL | HP_SDC_IM_RESET);
		hp_sdc.set_im = 1;
	}
	write_unlock_irq(&hp_sdc.hook_lock);
	tasklet_schedule(&hp_sdc.task);

	return 0;
}