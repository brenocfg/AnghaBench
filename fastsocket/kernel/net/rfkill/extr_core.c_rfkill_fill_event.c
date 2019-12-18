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
struct rfkill_event {int op; int hard; int soft; int /*<<< orphan*/  type; int /*<<< orphan*/  idx; } ;
struct rfkill {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; int /*<<< orphan*/  idx; } ;
typedef  enum rfkill_operation { ____Placeholder_rfkill_operation } rfkill_operation ;

/* Variables and functions */
 int RFKILL_BLOCK_HW ; 
 int RFKILL_BLOCK_SW ; 
 int RFKILL_BLOCK_SW_PREV ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rfkill_fill_event(struct rfkill_event *ev, struct rfkill *rfkill,
			      enum rfkill_operation op)
{
	unsigned long flags;

	ev->idx = rfkill->idx;
	ev->type = rfkill->type;
	ev->op = op;

	spin_lock_irqsave(&rfkill->lock, flags);
	ev->hard = !!(rfkill->state & RFKILL_BLOCK_HW);
	ev->soft = !!(rfkill->state & (RFKILL_BLOCK_SW |
					RFKILL_BLOCK_SW_PREV));
	spin_unlock_irqrestore(&rfkill->lock, flags);
}