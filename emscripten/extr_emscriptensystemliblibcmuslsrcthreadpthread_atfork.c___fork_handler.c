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
struct atfork_funcs {int /*<<< orphan*/  (* child ) () ;int /*<<< orphan*/  (* parent ) () ;struct atfork_funcs* prev; int /*<<< orphan*/  (* prepare ) () ;struct atfork_funcs* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 struct atfork_funcs* funcs ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 

void __fork_handler(int who)
{
	struct atfork_funcs *p;
	if (!funcs) return;
	if (who < 0) {
		LOCK(lock);
		for (p=funcs; p; p = p->next) {
			if (p->prepare) p->prepare();
			funcs = p;
		}
	} else {
		for (p=funcs; p; p = p->prev) {
			if (!who && p->parent) p->parent();
			else if (who && p->child) p->child();
			funcs = p;
		}
		UNLOCK(lock);
	}
}