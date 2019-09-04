#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct turnstile {int dummy; } ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_7__ {scalar_t__ ts_port_ref; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip_messages; } ;

/* Variables and functions */
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* port_send_turnstile (TYPE_1__*) ; 
 int /*<<< orphan*/  port_send_turnstile_address (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,int /*<<< orphan*/ ,struct turnstile**) ; 
 int /*<<< orphan*/  turnstile_deallocate_safe (struct turnstile*) ; 

void
ipc_port_send_turnstile_complete(ipc_port_t port)
{
	struct turnstile *turnstile = TURNSTILE_NULL;

	/* Drop turnstile count on dest port */
	imq_lock(&port->ip_messages);

	port_send_turnstile(port)->ts_port_ref--;
	if (port_send_turnstile(port)->ts_port_ref == 0) {
		turnstile_complete((uintptr_t)port, port_send_turnstile_address(port),
				&turnstile);
		assert(turnstile != TURNSTILE_NULL);
	}
	imq_unlock(&port->ip_messages);
	turnstile_cleanup();

	if (turnstile != TURNSTILE_NULL) {
		turnstile_deallocate_safe(turnstile);
		turnstile = TURNSTILE_NULL;
	}
}