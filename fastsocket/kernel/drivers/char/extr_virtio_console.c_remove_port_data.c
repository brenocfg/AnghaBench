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
struct port_buffer {int dummy; } ;
struct port {int /*<<< orphan*/  outvq_lock; int /*<<< orphan*/  out_vq; int /*<<< orphan*/  inbuf_lock; int /*<<< orphan*/  in_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_port_data (struct port*) ; 
 int /*<<< orphan*/  free_buf (struct port_buffer*) ; 
 int /*<<< orphan*/  reclaim_consumed_buffers (struct port*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct port_buffer* virtqueue_detach_unused_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_port_data(struct port *port)
{
	struct port_buffer *buf;

	spin_lock_irq(&port->inbuf_lock);
	/* Remove unused data this port might have received. */
	discard_port_data(port);

	/* Remove buffers we queued up for the Host to send us data in. */
	while ((buf = virtqueue_detach_unused_buf(port->in_vq)))
		free_buf(buf);
	spin_unlock_irq(&port->inbuf_lock);

	spin_lock_irq(&port->outvq_lock);
	reclaim_consumed_buffers(port);

	/* Free pending buffers from the out-queue. */
	while ((buf = virtqueue_detach_unused_buf(port->out_vq)))
		free_buf(buf);
	spin_unlock_irq(&port->outvq_lock);
}