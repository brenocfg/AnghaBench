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
struct raw3215_info {int flags; int /*<<< orphan*/  cdev; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int RAW3215_FROZEN ; 
 int RAW3215_TIMER_RUNS ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_mk_write_req (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_start_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void raw3215_timeout(unsigned long __data)
{
	struct raw3215_info *raw = (struct raw3215_info *) __data;
	unsigned long flags;

	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	if (raw->flags & RAW3215_TIMER_RUNS) {
		del_timer(&raw->timer);
		raw->flags &= ~RAW3215_TIMER_RUNS;
		if (!(raw->flags & RAW3215_FROZEN)) {
			raw3215_mk_write_req(raw);
			raw3215_start_io(raw);
		}
	}
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
}