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
struct vfe_interrupt_status {scalar_t__ violationIrq; scalar_t__ camifOverflowIrq; scalar_t__ camifErrorIrq; scalar_t__ busOverflowIrq; scalar_t__ axiErrorIrq; scalar_t__ awbOverflowIrq; scalar_t__ afOverflowIrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_MSG_ID_AF_OVERFLOW ; 
 int /*<<< orphan*/  VFE_MSG_ID_AWB_OVERFLOW ; 
 int /*<<< orphan*/  VFE_MSG_ID_AXI_ERROR ; 
 int /*<<< orphan*/  VFE_MSG_ID_CAMIF_OVERFLOW ; 
 int /*<<< orphan*/  vfe_send_bus_overflow_msg () ; 
 int /*<<< orphan*/  vfe_send_camif_error_msg () ; 
 int /*<<< orphan*/  vfe_send_msg_no_payload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_process_error_irq(
	struct vfe_interrupt_status *irqstatus)
{
	/* all possible error irq.  Note error irqs are not enabled, it is
	 * checked only when other interrupts are present. */
	if (irqstatus->afOverflowIrq)
		vfe_send_msg_no_payload(VFE_MSG_ID_AF_OVERFLOW);

	if (irqstatus->awbOverflowIrq)
		vfe_send_msg_no_payload(VFE_MSG_ID_AWB_OVERFLOW);

	if (irqstatus->axiErrorIrq)
		vfe_send_msg_no_payload(VFE_MSG_ID_AXI_ERROR);

	if (irqstatus->busOverflowIrq)
		vfe_send_bus_overflow_msg();

	if (irqstatus->camifErrorIrq)
		vfe_send_camif_error_msg();

	if (irqstatus->camifOverflowIrq)
		vfe_send_msg_no_payload(VFE_MSG_ID_CAMIF_OVERFLOW);

	if (irqstatus->violationIrq)
		;
}