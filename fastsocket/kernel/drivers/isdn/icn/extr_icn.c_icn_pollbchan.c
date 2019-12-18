#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  rb_timer; } ;
typedef  TYPE_1__ icn_card ;

/* Variables and functions */
 int ICN_FLAGS_B1ACTIVE ; 
 int ICN_FLAGS_B2ACTIVE ; 
 int ICN_FLAGS_RBTIMER ; 
 scalar_t__ ICN_TIMER_BCREAD ; 
 int /*<<< orphan*/  icn_pollbchan_receive (int,TYPE_1__*) ; 
 int /*<<< orphan*/  icn_pollbchan_send (int,TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
icn_pollbchan(unsigned long data)
{
	icn_card *card = (icn_card *) data;
	unsigned long flags;

	if (card->flags & ICN_FLAGS_B1ACTIVE) {
		icn_pollbchan_receive(0, card);
		icn_pollbchan_send(0, card);
	}
	if (card->flags & ICN_FLAGS_B2ACTIVE) {
		icn_pollbchan_receive(1, card);
		icn_pollbchan_send(1, card);
	}
	if (card->flags & (ICN_FLAGS_B1ACTIVE | ICN_FLAGS_B2ACTIVE)) {
		/* schedule b-channel polling again */
		spin_lock_irqsave(&card->lock, flags);
		mod_timer(&card->rb_timer, jiffies+ICN_TIMER_BCREAD);
		card->flags |= ICN_FLAGS_RBTIMER;
		spin_unlock_irqrestore(&card->lock, flags);
	} else
		card->flags &= ~ICN_FLAGS_RBTIMER;
}