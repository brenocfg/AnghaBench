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
struct vino_framebuffer_queue {scalar_t__ magic; unsigned int length; int /*<<< orphan*/  queue_lock; struct vino_framebuffer** buffer; int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;
struct vino_framebuffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ VINO_QUEUE_MAGIC ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vino_fifo_enqueue (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int vino_fifo_get_used (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vino_framebuffer *vino_queue_add(struct
					       vino_framebuffer_queue *q,
					       unsigned int id)
{
	struct vino_framebuffer *ret = NULL;
	unsigned int total;
	unsigned long flags;

	dprintk("vino_queue_add(): id = %d\n", id);

	if (q->magic != VINO_QUEUE_MAGIC) {
		return ret;
	}

	spin_lock_irqsave(&q->queue_lock, flags);

	if (q->length == 0)
		goto out;

	if (id >= q->length)
		goto out;

	/* not needed?: if (vino_fifo_full(&q->out)) {
		goto out;
		}*/
	/* check that outgoing queue isn't already full
	 * (or that it won't become full) */
	total = vino_fifo_get_used(&q->in) +
		vino_fifo_get_used(&q->out);
	if (total >= q->length)
		goto out;

	if (vino_fifo_enqueue(&q->in, id))
		goto out;

	ret = q->buffer[id];

out:
	spin_unlock_irqrestore(&q->queue_lock, flags);

	return ret;
}