#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  isdnloop_lock; TYPE_3__* c_timer; } ;
typedef  TYPE_1__ isdnloop_card ;
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ ISDNLOOP_TIMER_ALERTWAIT ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  isdnloop_atimeout0 ; 
 int /*<<< orphan*/  isdnloop_atimeout1 ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
isdnloop_start_ctimer(isdnloop_card * card, int ch)
{
	unsigned long flags;

	spin_lock_irqsave(&card->isdnloop_lock, flags);
	init_timer(&card->c_timer[ch]);
	card->c_timer[ch].expires = jiffies + ISDNLOOP_TIMER_ALERTWAIT;
	if (ch)
		card->c_timer[ch].function = isdnloop_atimeout1;
	else
		card->c_timer[ch].function = isdnloop_atimeout0;
	card->c_timer[ch].data = (unsigned long) card;
	add_timer(&card->c_timer[ch]);
	spin_unlock_irqrestore(&card->isdnloop_lock, flags);
}