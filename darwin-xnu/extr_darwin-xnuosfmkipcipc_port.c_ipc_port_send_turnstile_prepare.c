#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct turnstile {scalar_t__ ts_port_ref; } ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_8__ {scalar_t__ ip_receiver_name; int /*<<< orphan*/  ip_messages; struct TYPE_8__* ip_destination; } ;

/* Variables and functions */
 TYPE_1__* IP_NULL ; 
 scalar_t__ MACH_PORT_NULL ; 
 int TURNSTILE_IMMEDIATE_UPDATE ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_SYNC_IPC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ip_active (TYPE_1__*) ; 
 struct turnstile* ipc_port_get_inheritor (TYPE_1__*) ; 
 struct turnstile* port_send_turnstile (TYPE_1__*) ; 
 int /*<<< orphan*/  port_send_turnstile_address (TYPE_1__*) ; 
 struct turnstile* turnstile_alloc () ; 
 int /*<<< orphan*/  turnstile_deallocate (struct turnstile*) ; 
 struct turnstile* turnstile_prepare (uintptr_t,int /*<<< orphan*/ ,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,struct turnstile*,int) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

void
ipc_port_send_turnstile_prepare(ipc_port_t port)
{
	struct turnstile *turnstile = TURNSTILE_NULL;
	struct turnstile *inheritor = TURNSTILE_NULL;
	struct turnstile *send_turnstile = TURNSTILE_NULL;

retry_alloc:
	imq_lock(&port->ip_messages);

	if (port_send_turnstile(port) == NULL ||
	    port_send_turnstile(port)->ts_port_ref == 0) {

		if (turnstile == TURNSTILE_NULL) {
			imq_unlock(&port->ip_messages);
			turnstile = turnstile_alloc();
			goto retry_alloc;
		}

		send_turnstile = turnstile_prepare((uintptr_t)port,
			port_send_turnstile_address(port),
			turnstile, TURNSTILE_SYNC_IPC);
		turnstile = TURNSTILE_NULL;

		/*
		 * if port in transit, setup linkage for its turnstile,
		 * otherwise the link it to WL turnstile.
		 */
		if (ip_active(port) &&
		    port->ip_receiver_name == MACH_PORT_NULL &&
		    port->ip_destination != IP_NULL) {
			assert(port->ip_receiver_name == MACH_PORT_NULL);
			assert(port->ip_destination != IP_NULL);

			inheritor = port_send_turnstile(port->ip_destination);
		} else {
			inheritor = ipc_port_get_inheritor(port);
		}
		turnstile_update_inheritor(send_turnstile, inheritor,
			TURNSTILE_INHERITOR_TURNSTILE | TURNSTILE_IMMEDIATE_UPDATE);
		/* turnstile complete will be called in ipc_port_send_turnstile_complete */
	}

	/* Increment turnstile counter */
	port_send_turnstile(port)->ts_port_ref++;
	imq_unlock(&port->ip_messages);

	if (send_turnstile) {
		turnstile_update_inheritor_complete(send_turnstile,
			TURNSTILE_INTERLOCK_NOT_HELD);
	}
	if (turnstile != TURNSTILE_NULL) {
		turnstile_deallocate(turnstile);
	}
}