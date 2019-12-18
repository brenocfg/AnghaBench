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
struct sclp_register {int dummy; } ;
typedef  enum sclp_pm_event { ____Placeholder_sclp_pm_event } sclp_pm_event ;

/* Variables and functions */
#define  SCLP_PM_EVENT_FREEZE 130 
#define  SCLP_PM_EVENT_RESTORE 129 
#define  SCLP_PM_EVENT_THAW 128 
 int /*<<< orphan*/ * _machine_halt ; 
 int /*<<< orphan*/ * _machine_power_off ; 
 int /*<<< orphan*/ * _machine_restart ; 
 int /*<<< orphan*/ * old_machine_halt ; 
 int /*<<< orphan*/ * old_machine_power_off ; 
 int /*<<< orphan*/ * old_machine_restart ; 

__attribute__((used)) static void sclp_quiesce_pm_event(struct sclp_register *reg,
				  enum sclp_pm_event sclp_pm_event)
{
	switch (sclp_pm_event) {
	case SCLP_PM_EVENT_RESTORE:
		if (old_machine_restart) {
			_machine_restart = old_machine_restart;
			_machine_halt = old_machine_halt;
			_machine_power_off = old_machine_power_off;
			old_machine_restart = NULL;
			old_machine_halt = NULL;
			old_machine_power_off = NULL;
		}
		break;
	case SCLP_PM_EVENT_FREEZE:
	case SCLP_PM_EVENT_THAW:
		break;
	}
}