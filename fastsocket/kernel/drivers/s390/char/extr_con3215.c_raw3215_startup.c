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
struct raw3215_info {int flags; int /*<<< orphan*/  cdev; scalar_t__ line_pos; } ;

/* Variables and functions */
 int RAW3215_ACTIVE ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3215_try_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int raw3215_startup(struct raw3215_info *raw)
{
	unsigned long flags;

	if (raw->flags & RAW3215_ACTIVE)
		return 0;
	raw->line_pos = 0;
	raw->flags |= RAW3215_ACTIVE;
	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	raw3215_try_io(raw);
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);

	return 0;
}