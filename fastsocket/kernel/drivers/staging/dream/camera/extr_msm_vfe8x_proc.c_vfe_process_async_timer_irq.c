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
struct vfe_interrupt_status {scalar_t__ asyncTimer3Irq; scalar_t__ asyncTimer2Irq; scalar_t__ asyncTimer1Irq; scalar_t__ asyncTimer0Irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_MSG_ID_ASYNC_TIMER0_DONE ; 
 int /*<<< orphan*/  VFE_MSG_ID_ASYNC_TIMER1_DONE ; 
 int /*<<< orphan*/  VFE_MSG_ID_ASYNC_TIMER2_DONE ; 
 int /*<<< orphan*/  VFE_MSG_ID_ASYNC_TIMER3_DONE ; 
 int /*<<< orphan*/  vfe_send_msg_no_payload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_process_async_timer_irq(
	struct vfe_interrupt_status *irqstatus)
{

	if (irqstatus->asyncTimer0Irq)
		vfe_send_msg_no_payload(VFE_MSG_ID_ASYNC_TIMER0_DONE);

	if (irqstatus->asyncTimer1Irq)
		vfe_send_msg_no_payload(VFE_MSG_ID_ASYNC_TIMER1_DONE);

	if (irqstatus->asyncTimer2Irq)
		vfe_send_msg_no_payload(VFE_MSG_ID_ASYNC_TIMER2_DONE);

	if (irqstatus->asyncTimer3Irq)
		vfe_send_msg_no_payload(VFE_MSG_ID_ASYNC_TIMER3_DONE);
}