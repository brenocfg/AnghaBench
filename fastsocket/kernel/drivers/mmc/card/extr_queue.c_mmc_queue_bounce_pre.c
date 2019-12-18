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
struct mmc_queue {TYPE_1__* sg; int /*<<< orphan*/  bounce_buf; int /*<<< orphan*/  bounce_sg_len; int /*<<< orphan*/  bounce_sg; int /*<<< orphan*/  req; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ rq_data_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mmc_queue_bounce_pre(struct mmc_queue *mq)
{
	unsigned long flags;

	if (!mq->bounce_buf)
		return;

	if (rq_data_dir(mq->req) != WRITE)
		return;

	local_irq_save(flags);
	sg_copy_to_buffer(mq->bounce_sg, mq->bounce_sg_len,
		mq->bounce_buf, mq->sg[0].length);
	local_irq_restore(flags);
}