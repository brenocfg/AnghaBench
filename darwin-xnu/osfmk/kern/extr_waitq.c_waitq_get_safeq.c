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
struct waitq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct waitq* global_eventq (struct waitq*) ; 
 struct waitq* ipc_port_rcv_turnstile_waitq (struct waitq*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 scalar_t__ waitq_is_port_queue (struct waitq*) ; 

struct waitq * waitq_get_safeq(struct waitq *waitq)
{
	struct waitq *safeq;

	/* Check if it's a port waitq */
	if (waitq_is_port_queue(waitq)) {
		assert(!waitq_irq_safe(waitq));
		safeq = ipc_port_rcv_turnstile_waitq(waitq);
	} else {
		safeq = global_eventq(waitq);
	}
	return safeq;
}