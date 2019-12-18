#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bc_state {TYPE_2__* cs; int /*<<< orphan*/  channel; scalar_t__ busy; int /*<<< orphan*/  use_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ANY ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gigaset_free_channel(struct bc_state *bcs)
{
	unsigned long flags;

	spin_lock_irqsave(&bcs->cs->lock, flags);
	if (!bcs->busy) {
		gig_dbg(DEBUG_ANY, "could not free channel %d", bcs->channel);
		spin_unlock_irqrestore(&bcs->cs->lock, flags);
		return;
	}
	--bcs->use_count;
	bcs->busy = 0;
	module_put(bcs->cs->driver->owner);
	gig_dbg(DEBUG_ANY, "freed channel %d", bcs->channel);
	spin_unlock_irqrestore(&bcs->cs->lock, flags);
}