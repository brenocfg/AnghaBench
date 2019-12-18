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
struct tracepoint_entry {int /*<<< orphan*/  funcs; int /*<<< orphan*/  name; } ;
struct tracepoint {int state; int /*<<< orphan*/  funcs; int /*<<< orphan*/  (* unregfunc ) () ;int /*<<< orphan*/  (* regfunc ) () ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void set_tracepoint(struct tracepoint_entry **entry,
	struct tracepoint *elem, int active)
{
	WARN_ON(strcmp((*entry)->name, elem->name) != 0);

	if (elem->regfunc && !elem->state && active)
		elem->regfunc();
	else if (elem->unregfunc && elem->state && !active)
		elem->unregfunc();

	/*
	 * rcu_assign_pointer has a smp_wmb() which makes sure that the new
	 * probe callbacks array is consistent before setting a pointer to it.
	 * This array is referenced by __DO_TRACE from
	 * include/linux/tracepoints.h. A matching smp_read_barrier_depends()
	 * is used.
	 */
	rcu_assign_pointer(elem->funcs, (*entry)->funcs);
	elem->state = active;
}