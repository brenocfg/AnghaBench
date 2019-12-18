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
struct TYPE_2__ {int im; int set_im; int /*<<< orphan*/  task; int /*<<< orphan*/  hook_lock; int /*<<< orphan*/ * hil; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int HP_SDC_IM_HIL ; 
 int HP_SDC_IM_RESET ; 
 TYPE_1__ hp_sdc ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int hp_sdc_request_hil_irq(hp_sdc_irqhook *callback)
{
	if (callback == NULL || hp_sdc.dev == NULL)
		return -EINVAL;

	write_lock_irq(&hp_sdc.hook_lock);
	if (hp_sdc.hil != NULL) {
		write_unlock_irq(&hp_sdc.hook_lock);
		return -EBUSY;
	}

	hp_sdc.hil = callback;
	hp_sdc.im &= ~(HP_SDC_IM_HIL | HP_SDC_IM_RESET);
	hp_sdc.set_im = 1;
	write_unlock_irq(&hp_sdc.hook_lock);

	tasklet_schedule(&hp_sdc.task);

	return 0;
}