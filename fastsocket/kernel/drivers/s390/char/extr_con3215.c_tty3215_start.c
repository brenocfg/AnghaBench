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
struct tty_struct {scalar_t__ driver_data; } ;
struct raw3215_info {int flags; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int RAW3215_STOPPED ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_try_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void tty3215_start(struct tty_struct *tty)
{
	struct raw3215_info *raw;
	unsigned long flags;

	raw = (struct raw3215_info *) tty->driver_data;
	if (raw->flags & RAW3215_STOPPED) {
		spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
		raw->flags &= ~RAW3215_STOPPED;
		raw3215_try_io(raw);
		spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
	}
}