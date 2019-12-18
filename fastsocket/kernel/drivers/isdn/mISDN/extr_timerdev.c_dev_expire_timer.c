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
typedef  int /*<<< orphan*/  u_long ;
struct mISDNtimer {TYPE_1__* dev; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  expired; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dev_expire_timer(unsigned long data)
{
	struct mISDNtimer *timer = (void *)data;
	u_long			flags;

	spin_lock_irqsave(&timer->dev->lock, flags);
	list_move_tail(&timer->list, &timer->dev->expired);
	spin_unlock_irqrestore(&timer->dev->lock, flags);
	wake_up_interruptible(&timer->dev->wait);
}