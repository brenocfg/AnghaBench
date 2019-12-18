#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
struct turnstile {int dummy; } ;
typedef  TYPE_1__* ipc_space_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  scalar_t__ ipc_importance_task_t ;
typedef  int boolean_t ;
struct TYPE_20__ {scalar_t__ ip_impdonation; int ip_impcount; scalar_t__ ip_receiver_name; scalar_t__ ip_tempowner; scalar_t__ ip_imp_task; int /*<<< orphan*/  ip_messages; TYPE_1__* ip_receiver; struct TYPE_20__* ip_destination; } ;
struct TYPE_19__ {TYPE_16__* is_task; } ;
struct TYPE_18__ {scalar_t__ task_imp_base; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IIT_NULL ; 
 TYPE_2__* IP_NULL ; 
 scalar_t__ MACH_PORT_NULL ; 
 TYPE_16__* TASK_NULL ; 
 int TRUE ; 
 int TURNSTILE_IMMEDIATE_UPDATE ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_SYNC_IPC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imq_unlock (int /*<<< orphan*/ *) ; 
 int ip_active (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_2__*) ; 
 scalar_t__ ip_lock_try (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_lock_try () ; 
 int /*<<< orphan*/  ipc_importance_task_drop_internal_assertion_locked (scalar_t__,int) ; 
 int /*<<< orphan*/  ipc_importance_task_hold_internal_assertion_locked (scalar_t__,int) ; 
 int ipc_importance_task_is_any_receiver_type (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_task_reference (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_task_release (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  ipc_port_impcount_delta (TYPE_2__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_multiple_lock () ; 
 int /*<<< orphan*/  ipc_port_multiple_unlock () ; 
 int /*<<< orphan*/  ipc_port_send_turnstile_complete (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_send_turnstile_prepare (TYPE_2__*) ; 
 scalar_t__ port_send_turnstile (TYPE_2__*) ; 
 int /*<<< orphan*/  port_send_turnstile_address (TYPE_2__*) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct turnstile* turnstile_prepare (uintptr_t,int /*<<< orphan*/ ,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,scalar_t__,int) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

boolean_t
ipc_importance_check_circularity(
	ipc_port_t	port,
	ipc_port_t	dest)
{
	ipc_importance_task_t imp_task = IIT_NULL;
	ipc_importance_task_t release_imp_task = IIT_NULL;
	boolean_t imp_lock_held = FALSE;
	int assertcnt = 0;
	ipc_port_t base;
	struct turnstile *send_turnstile = TURNSTILE_NULL;

	assert(port != IP_NULL);
	assert(dest != IP_NULL);

	if (port == dest)
		return TRUE;
	base = dest;

	/* Check if destination needs a turnstile */
	ipc_port_send_turnstile_prepare(dest);

	/* port is in limbo, so donation status is safe to latch */
	if (port->ip_impdonation != 0) {
		imp_lock_held = TRUE;
		ipc_importance_lock();
	}

	/*
	 *	First try a quick check that can run in parallel.
	 *	No circularity if dest is not in transit.
	 */
	ip_lock(port);

	/* 
	 * Even if port is just carrying assertions for others,
	 * we need the importance lock.
	 */
	if (port->ip_impcount > 0 && !imp_lock_held) {
		if (!ipc_importance_lock_try()) {
			ip_unlock(port);
			ipc_importance_lock();
			ip_lock(port);
		}
		imp_lock_held = TRUE;
	}

	if (ip_lock_try(dest)) {
		if (!ip_active(dest) ||
		    (dest->ip_receiver_name != MACH_PORT_NULL) ||
		    (dest->ip_destination == IP_NULL))
			goto not_circular;

		/* dest is in transit; further checking necessary */

		ip_unlock(dest);
	}
	ip_unlock(port);

	/* 
	 * We're about to pay the cost to serialize,
	 * just go ahead and grab importance lock.
	 */
	if (!imp_lock_held) {
		ipc_importance_lock();
		imp_lock_held = TRUE;
	}

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

			/* base is in transit or in limbo */

			assert(ip_active(base));
			assert(base->ip_receiver_name == MACH_PORT_NULL);

			next = base->ip_destination;
			ip_unlock(base);
			base = next;
		}

		if (imp_lock_held)
			ipc_importance_unlock();

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
	/* port is in limbo */
	imq_lock(&port->ip_messages);

	assert(ip_active(port));
	assert(port->ip_receiver_name == MACH_PORT_NULL);
	assert(port->ip_destination == IP_NULL);

	ip_reference(dest);
	port->ip_destination = dest;

	/* must have been in limbo or still bound to a task */
	assert(port->ip_tempowner != 0);

	/*
	 * We delayed dropping assertions from a specific task.
	 * Cache that info now (we'll drop assertions and the
	 * task reference below).
	 */
	release_imp_task = port->ip_imp_task;
	if (IIT_NULL != release_imp_task) {
		port->ip_imp_task = IIT_NULL;
	}
	assertcnt = port->ip_impcount;

	/* take the port out of limbo w.r.t. assertions */
	port->ip_tempowner = 0;

	/*
	 * Setup linkage for source port if it has a send turnstile i.e. it has
	 * a thread waiting in send or has a port enqueued in it or has sync ipc
	 * push from a special reply port.
	 */
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
		/* every port along chain track assertions behind it */
		ipc_port_impcount_delta(dest, assertcnt, base);

		if (dest == base)
			break;

		/* port is in transit */

		assert(ip_active(dest));
		assert(dest->ip_receiver_name == MACH_PORT_NULL);
		assert(dest->ip_destination != IP_NULL);
		assert(dest->ip_tempowner == 0);

		next = dest->ip_destination;
		ip_unlock(dest);
		dest = next;
	}

	/* base is not in transit */
	assert(!ip_active(base) ||
	       (base->ip_receiver_name != MACH_PORT_NULL) ||
	       (base->ip_destination == IP_NULL));

	/*
	 * Find the task to boost (if any).
	 * We will boost "through" ports that don't know
	 * about inheritance to deliver receive rights that
	 * do.
	 */
	if (ip_active(base) && (assertcnt > 0)) {
		assert(imp_lock_held);
		if (base->ip_tempowner != 0) {
			if (IIT_NULL != base->ip_imp_task) {
				/* specified tempowner task */
				imp_task = base->ip_imp_task;
				assert(ipc_importance_task_is_any_receiver_type(imp_task));
			}
			/* otherwise don't boost current task */

		} else if (base->ip_receiver_name != MACH_PORT_NULL) {
			ipc_space_t space = base->ip_receiver;

			/* only spaces with boost-accepting tasks */
			if (space->is_task != TASK_NULL &&
			    ipc_importance_task_is_any_receiver_type(space->is_task->task_imp_base))
				imp_task = space->is_task->task_imp_base;
		}

		/* take reference before unlocking base */
		if (imp_task != IIT_NULL) {
			ipc_importance_task_reference(imp_task);
		}
	}

	ip_unlock(base);

	/*
	 * Transfer assertions now that the ports are unlocked.
	 * Avoid extra overhead if transferring to/from the same task.
	 *
	 * NOTE: If a transfer is occurring, the new assertions will
	 * be added to imp_task BEFORE the importance lock is unlocked.
	 * This is critical - to avoid decrements coming from the kmsgs
	 * beating the increment to the task.
	 */
	boolean_t transfer_assertions = (imp_task != release_imp_task);

	if (imp_task != IIT_NULL) {
		assert(imp_lock_held);
		if (transfer_assertions)
			ipc_importance_task_hold_internal_assertion_locked(imp_task, assertcnt);
	}

	if (release_imp_task != IIT_NULL) {
		assert(imp_lock_held);
		if (transfer_assertions)
			ipc_importance_task_drop_internal_assertion_locked(release_imp_task, assertcnt);
	}

	if (imp_lock_held)
		ipc_importance_unlock();

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

	if (imp_task != IIT_NULL)
		ipc_importance_task_release(imp_task);

	if (release_imp_task != IIT_NULL)
		ipc_importance_task_release(release_imp_task);

	return FALSE;
}