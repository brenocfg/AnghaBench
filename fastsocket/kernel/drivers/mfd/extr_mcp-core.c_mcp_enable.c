#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mcp {int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  use_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct mcp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mcp*) ; 

void mcp_enable(struct mcp *mcp)
{
	spin_lock_irq(&mcp->lock);
	if (mcp->use_count++ == 0)
		mcp->ops->enable(mcp);
	spin_unlock_irq(&mcp->lock);
}