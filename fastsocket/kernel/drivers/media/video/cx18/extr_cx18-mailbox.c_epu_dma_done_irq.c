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
typedef  scalar_t__ u32 ;
struct cx18_mdl_ack {int dummy; } ;
struct cx18_mailbox {scalar_t__* args; } ;
struct cx18_in_work_order {int flags; int /*<<< orphan*/  mdl_ack; struct cx18_mailbox mb; } ;
struct cx18 {scalar_t__ enc_mem; } ;

/* Variables and functions */
 int CX18_F_EWO_MB_STALE ; 
 scalar_t__ CX18_INVALID_TASK_HANDLE ; 
 scalar_t__ CX18_MAX_MDL_ACKS ; 
 int /*<<< orphan*/  cx18_memcpy_fromio (struct cx18*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  mb_ack_irq (struct cx18*,struct cx18_in_work_order*) ; 

__attribute__((used)) static int epu_dma_done_irq(struct cx18 *cx, struct cx18_in_work_order *order)
{
	u32 handle, mdl_ack_offset, mdl_ack_count;
	struct cx18_mailbox *mb;

	mb = &order->mb;
	handle = mb->args[0];
	mdl_ack_offset = mb->args[1];
	mdl_ack_count = mb->args[2];

	if (handle == CX18_INVALID_TASK_HANDLE ||
	    mdl_ack_count == 0 || mdl_ack_count > CX18_MAX_MDL_ACKS) {
		if ((order->flags & CX18_F_EWO_MB_STALE) == 0)
			mb_ack_irq(cx, order);
		return -1;
	}

	cx18_memcpy_fromio(cx, order->mdl_ack, cx->enc_mem + mdl_ack_offset,
			   sizeof(struct cx18_mdl_ack) * mdl_ack_count);

	if ((order->flags & CX18_F_EWO_MB_STALE) == 0)
		mb_ack_irq(cx, order);
	return 1;
}