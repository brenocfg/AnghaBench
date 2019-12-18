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
struct vino_framebuffer_queue {scalar_t__ magic; unsigned int length; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 scalar_t__ VINO_QUEUE_MAGIC ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int vino_queue_get_length(struct vino_framebuffer_queue *q)
{
	unsigned int length = 0;
	unsigned long flags;

	if (q->magic != VINO_QUEUE_MAGIC) {
		return length;
	}

	spin_lock_irqsave(&q->queue_lock, flags);
	length = q->length;
	spin_unlock_irqrestore(&q->queue_lock, flags);

	return length;
}