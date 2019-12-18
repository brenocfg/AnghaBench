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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ptimer; int /*<<< orphan*/  poll_tq; } ;
typedef  TYPE_1__ act2000_card ;

/* Variables and functions */
 int /*<<< orphan*/  act2000_receive (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
act2000_poll(unsigned long data)
{
	act2000_card * card = (act2000_card *)data;
	unsigned long flags;

	act2000_receive(&card->poll_tq);
	spin_lock_irqsave(&card->lock, flags);
	mod_timer(&card->ptimer, jiffies+3);
	spin_unlock_irqrestore(&card->lock, flags);
}