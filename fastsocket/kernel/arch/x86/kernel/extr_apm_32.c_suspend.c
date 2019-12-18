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
struct apm_user {int suspend_result; scalar_t__ suspend_wait; struct apm_user* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_NORMAL_RESUME ; 
 int APM_NO_ERROR ; 
 int /*<<< orphan*/  APM_STATE_SUSPEND ; 
 int APM_SUCCESS ; 
 int EIO ; 
 int /*<<< orphan*/  PMSG_RESUME ; 
 int /*<<< orphan*/  PMSG_SUSPEND ; 
 int /*<<< orphan*/  apm_error (char*,int) ; 
 int /*<<< orphan*/  apm_suspend_waitqueue ; 
 int /*<<< orphan*/  dpm_resume_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_resume_noirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_suspend_noirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_suspend_start (int /*<<< orphan*/ ) ; 
 int ignore_normal_resume ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  queue_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_timer () ; 
 int /*<<< orphan*/  restore_processor_state () ; 
 int /*<<< orphan*/  save_processor_state () ; 
 int set_system_power_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysdev_resume () ; 
 int /*<<< orphan*/  sysdev_suspend (int /*<<< orphan*/ ) ; 
 struct apm_user* user_list ; 
 int /*<<< orphan*/  user_list_lock ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int suspend(int vetoable)
{
	int err;
	struct apm_user	*as;

	dpm_suspend_start(PMSG_SUSPEND);

	dpm_suspend_noirq(PMSG_SUSPEND);

	local_irq_disable();
	sysdev_suspend(PMSG_SUSPEND);

	local_irq_enable();

	save_processor_state();
	err = set_system_power_state(APM_STATE_SUSPEND);
	ignore_normal_resume = 1;
	restore_processor_state();

	local_irq_disable();
	reinit_timer();

	if (err == APM_NO_ERROR)
		err = APM_SUCCESS;
	if (err != APM_SUCCESS)
		apm_error("suspend", err);
	err = (err == APM_SUCCESS) ? 0 : -EIO;

	sysdev_resume();
	local_irq_enable();

	dpm_resume_noirq(PMSG_RESUME);

	dpm_resume_end(PMSG_RESUME);
	queue_event(APM_NORMAL_RESUME, NULL);
	spin_lock(&user_list_lock);
	for (as = user_list; as != NULL; as = as->next) {
		as->suspend_wait = 0;
		as->suspend_result = err;
	}
	spin_unlock(&user_list_lock);
	wake_up_interruptible(&apm_suspend_waitqueue);
	return err;
}