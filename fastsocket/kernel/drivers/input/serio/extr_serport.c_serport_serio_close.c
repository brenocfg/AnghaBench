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
struct serport {int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct serio {struct serport* port_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERPORT_ACTIVE ; 
 int /*<<< orphan*/  SERPORT_DEAD ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serport_serio_close(struct serio *serio)
{
	struct serport *serport = serio->port_data;
	unsigned long flags;

	spin_lock_irqsave(&serport->lock, flags);
	clear_bit(SERPORT_ACTIVE, &serport->flags);
	set_bit(SERPORT_DEAD, &serport->flags);
	spin_unlock_irqrestore(&serport->lock, flags);

	wake_up_interruptible(&serport->wait);
}