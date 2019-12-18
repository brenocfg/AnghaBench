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
struct o2net_sock_container {int /*<<< orphan*/  sc_idle_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  o2net_sc_reset_idle_timer (struct o2net_sock_container*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_sc_postpone_idle(struct o2net_sock_container *sc)
{
	/* Only push out an existing timer */
	if (timer_pending(&sc->sc_idle_timeout))
		o2net_sc_reset_idle_timer(sc);
}