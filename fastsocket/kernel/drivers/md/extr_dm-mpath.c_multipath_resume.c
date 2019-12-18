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
struct multipath {int /*<<< orphan*/  lock; int /*<<< orphan*/  saved_queue_if_no_path; int /*<<< orphan*/  queue_if_no_path; } ;
struct dm_target {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void multipath_resume(struct dm_target *ti)
{
	struct multipath *m = (struct multipath *) ti->private;
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);
	m->queue_if_no_path = m->saved_queue_if_no_path;
	spin_unlock_irqrestore(&m->lock, flags);
}