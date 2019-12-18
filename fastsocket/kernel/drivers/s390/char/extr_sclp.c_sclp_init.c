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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext_int_info_hwc ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int register_early_external_interrupt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int register_reboot_notifier (int /*<<< orphan*/ *) ; 
 int sclp_check_interface () ; 
 int /*<<< orphan*/  sclp_init_mask (int) ; 
 scalar_t__ sclp_init_state ; 
 scalar_t__ sclp_init_state_initialized ; 
 scalar_t__ sclp_init_state_initializing ; 
 scalar_t__ sclp_init_state_uninitialized ; 
 int /*<<< orphan*/  sclp_interrupt_handler ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_reboot_notifier ; 
 int /*<<< orphan*/  sclp_reg_list ; 
 int /*<<< orphan*/  sclp_req_queue ; 
 int /*<<< orphan*/  sclp_request_timer ; 
 TYPE_1__ sclp_state_change_event ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sclp_init(void)
{
	unsigned long flags;
	int rc = 0;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Check for previous or running initialization */
	if (sclp_init_state != sclp_init_state_uninitialized)
		goto fail_unlock;
	sclp_init_state = sclp_init_state_initializing;
	/* Set up variables */
	INIT_LIST_HEAD(&sclp_req_queue);
	INIT_LIST_HEAD(&sclp_reg_list);
	list_add(&sclp_state_change_event.list, &sclp_reg_list);
	init_timer(&sclp_request_timer);
	/* Check interface */
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_check_interface();
	spin_lock_irqsave(&sclp_lock, flags);
	if (rc)
		goto fail_init_state_uninitialized;
	/* Register reboot handler */
	rc = register_reboot_notifier(&sclp_reboot_notifier);
	if (rc)
		goto fail_init_state_uninitialized;
	/* Register interrupt handler */
	rc = register_early_external_interrupt(0x2401, sclp_interrupt_handler,
					       &ext_int_info_hwc);
	if (rc)
		goto fail_unregister_reboot_notifier;
	sclp_init_state = sclp_init_state_initialized;
	spin_unlock_irqrestore(&sclp_lock, flags);
	/* Enable service-signal external interruption - needs to happen with
	 * IRQs enabled. */
	ctl_set_bit(0, 9);
	sclp_init_mask(1);
	return 0;

fail_unregister_reboot_notifier:
	unregister_reboot_notifier(&sclp_reboot_notifier);
fail_init_state_uninitialized:
	sclp_init_state = sclp_init_state_uninitialized;
fail_unlock:
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}