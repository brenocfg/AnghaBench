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
struct res_counter {int /*<<< orphan*/  lock; struct res_counter* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  res_counter_uncharge_locked (struct res_counter*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void res_counter_uncharge(struct res_counter *counter, unsigned long val)
{
	unsigned long flags;
	struct res_counter *c;

	local_irq_save(flags);
	for (c = counter; c != NULL; c = c->parent) {
		spin_lock(&c->lock);
		res_counter_uncharge_locked(c, val);
		spin_unlock(&c->lock);
	}
	local_irq_restore(flags);
}