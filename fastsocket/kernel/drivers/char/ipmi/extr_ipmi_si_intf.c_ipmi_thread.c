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
struct timespec {int dummy; } ;
struct smi_info {int /*<<< orphan*/  si_lock; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;

/* Variables and functions */
 int SI_SM_CALL_WITHOUT_DELAY ; 
 int SI_SM_CALL_WITH_DELAY ; 
 int SI_SM_IDLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ipmi_si_set_not_busy (struct timespec*) ; 
 int ipmi_thread_busy_wait (int,struct smi_info*,struct timespec*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int smi_event_handler (struct smi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ipmi_thread(void *data)
{
	struct smi_info *smi_info = data;
	unsigned long flags;
	enum si_sm_result smi_result;
	struct timespec busy_until;

	ipmi_si_set_not_busy(&busy_until);

	set_user_nice(current, 19);
	while (!kthread_should_stop()) {
		int busy_wait;

		spin_lock_irqsave(&(smi_info->si_lock), flags);
		smi_result = smi_event_handler(smi_info, 0);
		spin_unlock_irqrestore(&(smi_info->si_lock), flags);
		busy_wait = ipmi_thread_busy_wait(smi_result, smi_info,
						  &busy_until);

		if (smi_result == SI_SM_CALL_WITHOUT_DELAY)
			; /* do nothing */
		else if (smi_result == SI_SM_CALL_WITH_DELAY && busy_wait)
			schedule();
		else if (smi_result == SI_SM_IDLE)
			schedule_timeout_interruptible(100);
		else
			schedule_timeout_interruptible(1);
	}
	return 0;
}