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
struct tty_struct {scalar_t__ disc_data; } ;
struct serport {int /*<<< orphan*/  lock; int /*<<< orphan*/  serio; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERPORT_ACTIVE ; 
 int /*<<< orphan*/  serio_drv_write_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serport_ldisc_write_wakeup(struct tty_struct * tty)
{
	struct serport *serport = (struct serport *) tty->disc_data;
	unsigned long flags;

	spin_lock_irqsave(&serport->lock, flags);
	if (test_bit(SERPORT_ACTIVE, &serport->flags))
		serio_drv_write_wakeup(serport->serio);
	spin_unlock_irqrestore(&serport->lock, flags);
}