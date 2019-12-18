#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct turnstile {int dummy; } ;
typedef  TYPE_1__* ipc_port_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_16__ {scalar_t__ ip_receiver_name; int /*<<< orphan*/  ip_messages; struct TYPE_16__* ip_destination; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* IP_NULL ; 
 scalar_t__ MACH_PORT_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int TURNSTILE_IMMEDIATE_UPDATE ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_SYNC_IPC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 int ip_active (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 scalar_t__ ip_lock_try (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_importance_check_circularity (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_multiple_lock () ; 
 int /*<<< orphan*/  ipc_port_multiple_unlock () ; 
 int /*<<< orphan*/  ipc_port_send_turnstile_complete (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_send_turnstile_prepare (TYPE_1__*) ; 
 scalar_t__ port_send_turnstile (TYPE_1__*) ; 
 int /*<<< orphan*/  port_send_turnstile_address (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct turnstile* turnstile_prepare (uintptr_t,int /*<<< orphan*/ ,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,scalar_t__,int) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

boolean_t
ipc_port_check_circularity(
	ipc_port_t	port,
	ipc_port_t	dest)
{
#if IMPORTANCE_INHERITANCE
	/* adjust importance counts at the same time */
	return ipc_importance_check_circularity(port, dest);
#else
	ipc_port_t base;

	assert(port != IP_NULL);
	assert(dest != IP_NULL);

	if (port == dest)
		return TRUE;
	base = dest;

	/* Check if destination needs a turnstile */
	ipc_port_send_turnstile_prepare(dest);

	/*
	 *	First try a quick check that can run in parallel.
	 *	No circularity if dest is not in transit.
	 */
	ip_lock(port);
	if (ip_lock_try(dest)) {
		if (!ip_active(dest) ||
		    (dest->ip_receiver_name != MACH_PORT_NULL) ||
		    (dest->ip_destination == IP_NULL))
			goto not_circular;

		/* dest is in transit; further checking necessary */

		ip_unlock(dest);
	}
	ip_unlock(port);

	ipc_port_multiple_lock(); /* massive serialization */

	/*
	 *	Search for the end of the chain (a port not in transit),
	 *	acquiring locks along the way.
	 */

	for (;;) {
		ip_lock(base);

		if (!ip_active(base) ||
		    (base->ip_receiver_name != MACH_PORT_NULL) ||
		    (base->ip_destination == IP_NULL))
			break;

		base = base->ip_destination;
	}

	/* all ports in chain from dest to base, inclusive, are locked */

	if (port == base) {
		/* circularity detected! */

		ipc_port_multiple_unlock();

		/* port (== base) is in limbo */

		assert(ip_active(port));
		assert(port->ip_receiver_name == MACH_PORT_NULL);
		assert(port->ip_destination == IP_NULL);

		base = dest;
		while (base != IP_NULL) {
			ipc_port_t next;

			/* dest is in transit or in limbo */

			assert(ip_active(base));
			assert(base->ip_receiver_name == MACH_PORT_NULL);

			next = base->ip_destination;
			ip_unlock(base);
			base = next;
		}

		ipc_port_send_turnstile_complete(dest);
		return TRUE;
	}

	/*
	 *	The guarantee:  lock port while the entire chain is locked.
	 *	Once port is locked, we can take a reference to dest,
	 *	add port to the chain, and unlock everything.
	 */

	ip_lock(port);
	ipc_port_multiple_unlock();

not_circular:
	imq_lock(&port->ip_messages);

	/* port is in limbo */

	assert(ip_active(port));
	assert(port->ip_receiver_name == MACH_PORT_NULL);
	assert(port->ip_destination == IP_NULL);

	ip_reference(dest);
	port->ip_destination = dest;

	/* Setup linkage for source port if it has sync ipc push */
	struct turnstile *send_turnstile = TURNSTILE_NULL;
	if (port_send_turnstile(port)) {
		send_turnstile = turnstile_prepare((uintptr_t)port,
			port_send_turnstile_address(port),
			TURNSTILE_NULL, TURNSTILE_SYNC_IPC);

		turnstile_update_inheritor(send_turnstile, port_send_turnstile(dest),
			(TURNSTILE_INHERITOR_TURNSTILE | TURNSTILE_IMMEDIATE_UPDATE));

		/* update complete and turnstile complete called after dropping all locks */
	}
	imq_unlock(&port->ip_messages);

	/* now unlock chain */

	ip_unlock(port);

	for (;;) {
		ipc_port_t next;

		if (dest == base)
			break;

		/* port is in transit */

		assert(ip_active(dest));
		assert(dest->ip_receiver_name == MACH_PORT_NULL);
		assert(dest->ip_destination != IP_NULL);

		next = dest->ip_destination;
		ip_unlock(dest);
		dest = next;
	}

	/* base is not in transit */
	assert(!ip_active(base) ||
	       (base->ip_receiver_name != MACH_PORT_NULL) ||
	       (base->ip_destination == IP_NULL));

	ip_unlock(base);

	/* All locks dropped, call turnstile_update_inheritor_complete for source port's turnstile */
	if (send_turnstile) {
		turnstile_update_inheritor_complete(send_turnstile, TURNSTILE_INTERLOCK_NOT_HELD);

		/* Take the mq lock to call turnstile complete */
		imq_lock(&port->ip_messages);
		turnstile_complete((uintptr_t)port, port_send_turnstile_address(port), NULL);
		send_turnstile = TURNSTILE_NULL;
		imq_unlock(&port->ip_messages);
		turnstile_cleanup();
	}

	return FALSE;
#endif /* !IMPORTANCE_INHERITANCE */
}