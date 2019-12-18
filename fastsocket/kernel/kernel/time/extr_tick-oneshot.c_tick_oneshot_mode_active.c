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
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ TICKDEV_MODE_ONESHOT ; 
 TYPE_1__ __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  tick_cpu_device ; 

int tick_oneshot_mode_active(void)
{
	unsigned long flags;
	int ret;

	local_irq_save(flags);
	ret = __get_cpu_var(tick_cpu_device).mode == TICKDEV_MODE_ONESHOT;
	local_irq_restore(flags);

	return ret;
}