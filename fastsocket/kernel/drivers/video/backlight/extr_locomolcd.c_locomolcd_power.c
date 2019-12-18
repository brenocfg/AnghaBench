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
struct TYPE_2__ {int comadj; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  locomolcd_dev ; 
 int /*<<< orphan*/  locomolcd_off (int) ; 
 int /*<<< orphan*/  locomolcd_on (int) ; 
 scalar_t__ machine_is_collie () ; 
 scalar_t__ machine_is_poodle () ; 
 TYPE_1__ sharpsl_param ; 

void locomolcd_power(int on)
{
	int comadj = sharpsl_param.comadj;
	unsigned long flags;

	local_irq_save(flags);

	if (!locomolcd_dev) {
		local_irq_restore(flags);
		return;
	}

	/* read comadj */
	if (comadj == -1 && machine_is_collie())
		comadj = 128;
	if (comadj == -1 && machine_is_poodle())
		comadj = 118;

	if (on)
		locomolcd_on(comadj);
	else
		locomolcd_off(comadj);

	local_irq_restore(flags);
}