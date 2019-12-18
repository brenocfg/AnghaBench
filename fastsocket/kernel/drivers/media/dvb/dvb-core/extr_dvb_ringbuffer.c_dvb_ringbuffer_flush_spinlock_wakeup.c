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
struct dvb_ringbuffer {int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_ringbuffer_flush (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dvb_ringbuffer_flush_spinlock_wakeup(struct dvb_ringbuffer *rbuf)
{
	unsigned long flags;

	spin_lock_irqsave(&rbuf->lock, flags);
	dvb_ringbuffer_flush(rbuf);
	spin_unlock_irqrestore(&rbuf->lock, flags);

	wake_up(&rbuf->queue);
}