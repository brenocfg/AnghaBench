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
struct mon_reader {int /*<<< orphan*/  r_link; } ;
struct mon_bus {scalar_t__ nreaders; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mon_bus_drop ; 
 int /*<<< orphan*/  mon_stop (struct mon_bus*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mon_reader_del(struct mon_bus *mbus, struct mon_reader *r)
{
	unsigned long flags;

	spin_lock_irqsave(&mbus->lock, flags);
	list_del(&r->r_link);
	--mbus->nreaders;
	if (mbus->nreaders == 0)
		mon_stop(mbus);
	spin_unlock_irqrestore(&mbus->lock, flags);

	kref_put(&mbus->ref, mon_bus_drop);
}