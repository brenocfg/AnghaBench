#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_8__ {scalar_t__ expires; } ;
struct TYPE_5__ {TYPE_4__ timer; } ;
struct TYPE_6__ {TYPE_1__ hfc; } ;
struct IsdnCardState {TYPE_2__ hw; int /*<<< orphan*/  lock; TYPE_3__* bcs; } ;
struct TYPE_7__ {scalar_t__ mode; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  main_irq_hfc (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TeleInt_Timer(struct IsdnCardState *cs)
{
	int stat = 0;
	u_long flags;
	
	spin_lock_irqsave(&cs->lock, flags);
	if (cs->bcs[0].mode) {
		stat |= 1;
		main_irq_hfc(&cs->bcs[0]);
	}
	if (cs->bcs[1].mode) {
		stat |= 2;
		main_irq_hfc(&cs->bcs[1]);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
	stat = HZ/100;
	if (!stat)
		stat = 1;
	cs->hw.hfc.timer.expires = jiffies + stat;
	add_timer(&cs->hw.hfc.timer);
}