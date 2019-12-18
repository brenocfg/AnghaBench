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
struct per_user_data {scalar_t__ ring_prod; scalar_t__ ring_cons; unsigned int* ring; int ring_overflow; int /*<<< orphan*/  evtchn_async_queue; int /*<<< orphan*/  evtchn_wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t EVTCHN_RING_MASK (scalar_t__) ; 
 scalar_t__ EVTCHN_RING_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct per_user_data** port_user ; 
 int /*<<< orphan*/  port_user_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

irqreturn_t evtchn_interrupt(int irq, void *data)
{
	unsigned int port = (unsigned long)data;
	struct per_user_data *u;

	spin_lock(&port_user_lock);

	u = port_user[port];

	disable_irq_nosync(irq);

	if ((u->ring_prod - u->ring_cons) < EVTCHN_RING_SIZE) {
		u->ring[EVTCHN_RING_MASK(u->ring_prod)] = port;
		wmb(); /* Ensure ring contents visible */
		if (u->ring_cons == u->ring_prod++) {
			wake_up_interruptible(&u->evtchn_wait);
			kill_fasync(&u->evtchn_async_queue,
				    SIGIO, POLL_IN);
		}
	} else {
		u->ring_overflow = 1;
	}

	spin_unlock(&port_user_lock);

	return IRQ_HANDLED;
}