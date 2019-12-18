#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rng; } ;
struct TYPE_4__ {int /*<<< orphan*/  ri_down; int /*<<< orphan*/  ri_up; } ;
struct slgt_info {int /*<<< orphan*/  pending_bh; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; TYPE_1__ icount; int /*<<< orphan*/  ri_chkcount; int /*<<< orphan*/  signals; int /*<<< orphan*/  device_name; TYPE_2__ input_signal_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_STATUS ; 
 unsigned short BIT0 ; 
 int /*<<< orphan*/  DBGISR (char*) ; 
 scalar_t__ IO_PIN_SHUTDOWN_LIMIT ; 
 int /*<<< orphan*/  IRQ_RI ; 
 int /*<<< orphan*/  SerialSignal_RI ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ri_change(struct slgt_info *info, unsigned short status)
{
	if (status & BIT0) {
		info->signals |= SerialSignal_RI;
		info->input_signal_events.ri_up++;
	} else {
		info->signals &= ~SerialSignal_RI;
		info->input_signal_events.ri_down++;
	}
	DBGISR(("ri_change %s signals=%04X\n", info->device_name, info->signals));
	if ((info->ri_chkcount)++ == IO_PIN_SHUTDOWN_LIMIT) {
		slgt_irq_off(info, IRQ_RI);
		return;
	}
	info->icount.rng++;
	wake_up_interruptible(&info->status_event_wait_q);
	wake_up_interruptible(&info->event_wait_q);
	info->pending_bh |= BH_STATUS;
}