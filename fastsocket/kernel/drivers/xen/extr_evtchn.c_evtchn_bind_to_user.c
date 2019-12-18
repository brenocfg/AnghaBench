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
struct per_user_data {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int bind_evtchn_to_irqhandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  evtchn_interrupt ; 
 struct per_user_data** port_user ; 

__attribute__((used)) static int evtchn_bind_to_user(struct per_user_data *u, int port)
{
	int rc = 0;

	/*
	 * Ports are never reused, so every caller should pass in a
	 * unique port.
	 *
	 * (Locking not necessary because we haven't registered the
	 * interrupt handler yet, and our caller has already
	 * serialized bind operations.)
	 */
	BUG_ON(port_user[port] != NULL);
	port_user[port] = u;

	rc = bind_evtchn_to_irqhandler(port, evtchn_interrupt, IRQF_DISABLED,
				       u->name, (void *)(unsigned long)port);
	if (rc >= 0)
		rc = 0;

	return rc;
}