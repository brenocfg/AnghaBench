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
struct turnstile {struct waitq ts_waitq; } ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_mqueue_t ;

/* Variables and functions */
 struct turnstile* TURNSTILE_NULL ; 
 struct waitq* global_eventq (struct waitq*) ; 
 int /*<<< orphan*/  imq_from_waitq (struct waitq*) ; 
 int /*<<< orphan*/  ip_from_mq (int /*<<< orphan*/ ) ; 
 struct turnstile* ipc_port_rcv_turnstile (int /*<<< orphan*/ ) ; 

struct waitq *
ipc_port_rcv_turnstile_waitq(struct waitq *waitq)
{
	struct waitq *safeq;

	ipc_mqueue_t mqueue = imq_from_waitq(waitq);
	ipc_port_t port = ip_from_mq(mqueue);
	struct turnstile *rcv_turnstile = ipc_port_rcv_turnstile(port);

	/* Check if the port has a rcv turnstile */
	if (rcv_turnstile != TURNSTILE_NULL) {
		safeq = &rcv_turnstile->ts_waitq;
	} else {
		safeq = global_eventq(waitq);
	}
	return safeq;
}