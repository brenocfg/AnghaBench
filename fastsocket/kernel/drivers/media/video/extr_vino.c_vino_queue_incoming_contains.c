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
struct vino_framebuffer_queue {scalar_t__ magic; scalar_t__ length; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 scalar_t__ VINO_QUEUE_MAGIC ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vino_fifo_has_id (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int vino_queue_incoming_contains(struct vino_framebuffer_queue *q,
					unsigned int id)
{
	int ret = 0;
	unsigned long flags;

	if (q->magic != VINO_QUEUE_MAGIC) {
		return ret;
	}

	spin_lock_irqsave(&q->queue_lock, flags);

	if (q->length == 0)
		goto out;

	ret = vino_fifo_has_id(&q->in, id);

out:
	spin_unlock_irqrestore(&q->queue_lock, flags);

	return ret;
}