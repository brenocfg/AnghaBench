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
struct srp_target_port {int connected; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool srp_change_conn_state(struct srp_target_port *target,
				  bool connected)
{
	bool changed = false;

	spin_lock_irq(&target->lock);
	if (target->connected != connected) {
		target->connected = connected;
		changed = true;
	}
	spin_unlock_irq(&target->lock);

	return changed;
}