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
struct raw3215_info {scalar_t__ count; int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3215_FLUSHING ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_try_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void raw3215_flush_buffer(struct raw3215_info *raw)
{
	unsigned long flags;

	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	if (raw->count > 0) {
		raw->flags |= RAW3215_FLUSHING;
		raw3215_try_io(raw);
		raw->flags &= ~RAW3215_FLUSHING;
	}
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
}