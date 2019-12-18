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
struct priority_group {int bypassed; } ;
struct multipath {int /*<<< orphan*/  trigger_event; int /*<<< orphan*/  lock; int /*<<< orphan*/ * current_pg; int /*<<< orphan*/ * current_pgpath; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bypass_pg(struct multipath *m, struct priority_group *pg,
		      int bypassed)
{
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);

	pg->bypassed = bypassed;
	m->current_pgpath = NULL;
	m->current_pg = NULL;

	spin_unlock_irqrestore(&m->lock, flags);

	schedule_work(&m->trigger_event);
}