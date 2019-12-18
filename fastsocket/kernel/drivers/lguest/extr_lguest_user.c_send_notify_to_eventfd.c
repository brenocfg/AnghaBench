#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lg_eventfd_map {unsigned int num; TYPE_2__* map; } ;
struct lg_cpu {scalar_t__ pending_notify; TYPE_1__* lg; } ;
struct TYPE_4__ {scalar_t__ addr; int /*<<< orphan*/  event; } ;
struct TYPE_3__ {int /*<<< orphan*/  eventfds; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_signal (int /*<<< orphan*/ ,int) ; 
 struct lg_eventfd_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool send_notify_to_eventfd(struct lg_cpu *cpu)
{
	unsigned int i;
	struct lg_eventfd_map *map;

	/*
	 * This "rcu_read_lock()" helps track when someone is still looking at
	 * the (RCU-using) eventfds array.  It's not actually a lock at all;
	 * indeed it's a noop in many configurations.  (You didn't expect me to
	 * explain all the RCU secrets here, did you?)
	 */
	rcu_read_lock();
	/*
	 * rcu_dereference is the counter-side of rcu_assign_pointer(); it
	 * makes sure we don't access the memory pointed to by
	 * cpu->lg->eventfds before cpu->lg->eventfds is set.  Sounds crazy,
	 * but Alpha allows this!  Paul McKenney points out that a really
	 * aggressive compiler could have the same effect:
	 *   http://lists.ozlabs.org/pipermail/lguest/2009-July/001560.html
	 *
	 * So play safe, use rcu_dereference to get the rcu-protected pointer:
	 */
	map = rcu_dereference(cpu->lg->eventfds);
	/*
	 * Simple array search: even if they add an eventfd while we do this,
	 * we'll continue to use the old array and just won't see the new one.
	 */
	for (i = 0; i < map->num; i++) {
		if (map->map[i].addr == cpu->pending_notify) {
			eventfd_signal(map->map[i].event, 1);
			cpu->pending_notify = 0;
			break;
		}
	}
	/* We're done with the rcu-protected variable cpu->lg->eventfds. */
	rcu_read_unlock();

	/* If we cleared the notification, it's because we found a match. */
	return cpu->pending_notify == 0;
}