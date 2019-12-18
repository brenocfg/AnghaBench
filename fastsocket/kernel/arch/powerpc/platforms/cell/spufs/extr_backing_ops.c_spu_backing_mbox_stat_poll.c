#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  int_mask_class2_RW; int /*<<< orphan*/  int_stat_class2_RW; } ;
struct TYPE_4__ {int mb_stat_R; } ;
struct TYPE_6__ {int /*<<< orphan*/  register_lock; TYPE_2__ priv1; TYPE_1__ prob; } ;
struct spu_context {TYPE_3__ csa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS2_ENABLE_MAILBOX_INTR ; 
 int /*<<< orphan*/  CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR ; 
 int /*<<< orphan*/  CLASS2_MAILBOX_INTR ; 
 int /*<<< orphan*/  CLASS2_MAILBOX_THRESHOLD_INTR ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int spu_backing_mbox_stat_poll(struct spu_context *ctx,
					  unsigned int events)
{
	int ret;
	u32 stat;

	ret = 0;
	spin_lock_irq(&ctx->csa.register_lock);
	stat = ctx->csa.prob.mb_stat_R;

	/* if the requested event is there, return the poll
	   mask, otherwise enable the interrupt to get notified,
	   but first mark any pending interrupts as done so
	   we don't get woken up unnecessarily */

	if (events & (POLLIN | POLLRDNORM)) {
		if (stat & 0xff0000)
			ret |= POLLIN | POLLRDNORM;
		else {
			ctx->csa.priv1.int_stat_class2_RW &=
				~CLASS2_MAILBOX_INTR;
			ctx->csa.priv1.int_mask_class2_RW |=
				CLASS2_ENABLE_MAILBOX_INTR;
		}
	}
	if (events & (POLLOUT | POLLWRNORM)) {
		if (stat & 0x00ff00)
			ret = POLLOUT | POLLWRNORM;
		else {
			ctx->csa.priv1.int_stat_class2_RW &=
				~CLASS2_MAILBOX_THRESHOLD_INTR;
			ctx->csa.priv1.int_mask_class2_RW |=
				CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR;
		}
	}
	spin_unlock_irq(&ctx->csa.register_lock);
	return ret;
}