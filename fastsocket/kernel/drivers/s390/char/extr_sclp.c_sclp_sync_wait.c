#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ) ;scalar_t__ expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ctl_load (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_local_irq_stosm (int) ; 
 int /*<<< orphan*/  _local_bh_enable () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ del_timer (TYPE_1__*) ; 
 scalar_t__ get_clock () ; 
 int in_interrupt () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long long local_tick_disable () ; 
 int /*<<< orphan*/  local_tick_enable (unsigned long long) ; 
 TYPE_1__ sclp_request_timer ; 
 scalar_t__ sclp_running_state ; 
 scalar_t__ sclp_running_state_idle ; 
 scalar_t__ sclp_tod_from_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_hardirqs_on () ; 

void
sclp_sync_wait(void)
{
	unsigned long long old_tick;
	unsigned long flags;
	unsigned long cr0, cr0_sync;
	u64 timeout;
	int irq_context;

	/* We'll be disabling timer interrupts, so we need a custom timeout
	 * mechanism */
	timeout = 0;
	if (timer_pending(&sclp_request_timer)) {
		/* Get timeout TOD value */
		timeout = get_clock() +
			  sclp_tod_from_jiffies(sclp_request_timer.expires -
						jiffies);
	}
	local_irq_save(flags);
	/* Prevent bottom half from executing once we force interrupts open */
	irq_context = in_interrupt();
	if (!irq_context)
		local_bh_disable();
	/* Enable service-signal interruption, disable timer interrupts */
	old_tick = local_tick_disable();
	trace_hardirqs_on();
	__ctl_store(cr0, 0, 0);
	cr0_sync = cr0;
	cr0_sync &= 0xffff00a0;
	cr0_sync |= 0x00000200;
	__ctl_load(cr0_sync, 0, 0);
	__raw_local_irq_stosm(0x01);
	/* Loop until driver state indicates finished request */
	while (sclp_running_state != sclp_running_state_idle) {
		/* Check for expired request timer */
		if (timer_pending(&sclp_request_timer) &&
		    get_clock() > timeout &&
		    del_timer(&sclp_request_timer))
			sclp_request_timer.function(sclp_request_timer.data);
		cpu_relax();
	}
	local_irq_disable();
	__ctl_load(cr0, 0, 0);
	if (!irq_context)
		_local_bh_enable();
	local_tick_enable(old_tick);
	local_irq_restore(flags);
}