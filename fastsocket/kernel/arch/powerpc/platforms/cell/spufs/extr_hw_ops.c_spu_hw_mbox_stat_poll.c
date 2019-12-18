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
typedef  int u32 ;
struct spu_context {struct spu* spu; } ;
struct spu {int /*<<< orphan*/  register_lock; TYPE_1__* problem; } ;
struct TYPE_2__ {int /*<<< orphan*/  mb_stat_R; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS2_ENABLE_MAILBOX_INTR ; 
 int /*<<< orphan*/  CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR ; 
 int /*<<< orphan*/  CLASS2_MAILBOX_INTR ; 
 int /*<<< orphan*/  CLASS2_MAILBOX_THRESHOLD_INTR ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_int_mask_or (struct spu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_int_stat_clear (struct spu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int spu_hw_mbox_stat_poll(struct spu_context *ctx,
					  unsigned int events)
{
	struct spu *spu = ctx->spu;
	int ret = 0;
	u32 stat;

	spin_lock_irq(&spu->register_lock);
	stat = in_be32(&spu->problem->mb_stat_R);

	/* if the requested event is there, return the poll
	   mask, otherwise enable the interrupt to get notified,
	   but first mark any pending interrupts as done so
	   we don't get woken up unnecessarily */

	if (events & (POLLIN | POLLRDNORM)) {
		if (stat & 0xff0000)
			ret |= POLLIN | POLLRDNORM;
		else {
			spu_int_stat_clear(spu, 2, CLASS2_MAILBOX_INTR);
			spu_int_mask_or(spu, 2, CLASS2_ENABLE_MAILBOX_INTR);
		}
	}
	if (events & (POLLOUT | POLLWRNORM)) {
		if (stat & 0x00ff00)
			ret = POLLOUT | POLLWRNORM;
		else {
			spu_int_stat_clear(spu, 2,
					CLASS2_MAILBOX_THRESHOLD_INTR);
			spu_int_mask_or(spu, 2,
					CLASS2_ENABLE_MAILBOX_THRESHOLD_INTR);
		}
	}
	spin_unlock_irq(&spu->register_lock);
	return ret;
}