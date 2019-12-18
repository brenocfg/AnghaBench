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
struct virtqueue {int dummy; } ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {size_t bytes_sent; } ;
struct port {int outvq_full; TYPE_1__ stats; int /*<<< orphan*/  outvq_lock; struct virtqueue* out_vq; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  reclaim_consumed_buffers (struct port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ virtqueue_add_buf (struct virtqueue*,struct scatterlist*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static ssize_t __send_to_port(struct port *port, struct scatterlist *sg,
			      int nents, size_t in_count,
			      void *data, bool nonblock)
{
	struct virtqueue *out_vq;
	ssize_t ret;
	unsigned long flags;
	unsigned int len;

	out_vq = port->out_vq;

	spin_lock_irqsave(&port->outvq_lock, flags);

	reclaim_consumed_buffers(port);

	ret = virtqueue_add_buf(out_vq, sg, nents, 0, data);

	/* Tell Host to go! */
	virtqueue_kick(out_vq);

	if (ret < 0) {
		in_count = 0;
		goto done;
	}

	if (ret == 0)
		port->outvq_full = true;

	if (nonblock)
		goto done;

	/*
	 * Wait till the host acknowledges it pushed out the data we
	 * sent.  This is done for data from the hvc_console; the tty
	 * operations are performed with spinlocks held so we can't
	 * sleep here.  An alternative would be to copy the data to a
	 * buffer and relax the spinning requirement.  The downside is
	 * we need to kmalloc a GFP_ATOMIC buffer each time the
	 * console driver writes something out.
	 */
	while (!virtqueue_get_buf(out_vq, &len))
		cpu_relax();
done:
	spin_unlock_irqrestore(&port->outvq_lock, flags);

	port->stats.bytes_sent += in_count;
	/*
	 * We're expected to return the amount of data we wrote -- all
	 * of it
	 */
	return in_count;
}