#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct TYPE_4__ {int devicename; int /*<<< orphan*/ * ioport; int /*<<< orphan*/  lock; TYPE_2__ reset_timer; scalar_t__ EngineUp; int /*<<< orphan*/  stat_timer; } ;

/* Variables and functions */
 scalar_t__ CHECKRESET_TIME ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISDN_STAT_STOP ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 size_t SFT_RESET ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  indicate_status (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 TYPE_1__** sc_adapter ; 
 int /*<<< orphan*/  sc_check_reset ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int reset(int card)
{
	unsigned long flags;

	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	indicate_status(card, ISDN_STAT_STOP, 0, NULL);

	if(sc_adapter[card]->EngineUp) {
		del_timer(&sc_adapter[card]->stat_timer);
	}

	sc_adapter[card]->EngineUp = 0;

	spin_lock_irqsave(&sc_adapter[card]->lock, flags);
	init_timer(&sc_adapter[card]->reset_timer);
	sc_adapter[card]->reset_timer.function = sc_check_reset;
	sc_adapter[card]->reset_timer.data = card;
	sc_adapter[card]->reset_timer.expires = jiffies + CHECKRESET_TIME;
	add_timer(&sc_adapter[card]->reset_timer);
	spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);

	outb(0x1,sc_adapter[card]->ioport[SFT_RESET]);

	pr_debug("%s: Adapter Reset\n", sc_adapter[card]->devicename);
	return 0;
}