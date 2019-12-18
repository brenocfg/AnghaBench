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

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int xpc_activate_IRQ_rcvd ; 
 int /*<<< orphan*/  xpc_activate_IRQ_rcvd_lock ; 
 int xpc_identify_activate_IRQ_sender_sn2 () ; 

__attribute__((used)) static void
xpc_process_activate_IRQ_rcvd_sn2(void)
{
	unsigned long irq_flags;
	int n_IRQs_expected;
	int n_IRQs_detected;

	spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
	n_IRQs_expected = xpc_activate_IRQ_rcvd;
	xpc_activate_IRQ_rcvd = 0;
	spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

	n_IRQs_detected = xpc_identify_activate_IRQ_sender_sn2();
	if (n_IRQs_detected < n_IRQs_expected) {
		/* retry once to help avoid missing amo */
		(void)xpc_identify_activate_IRQ_sender_sn2();
	}
}