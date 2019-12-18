#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int last_state; int /*<<< orphan*/  priv; int /*<<< orphan*/  (* notify ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* recv; int /*<<< orphan*/  (* update_state ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ smd_channel_t ;
struct TYPE_5__ {unsigned int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMD_EVENT_CLOSE ; 
 int /*<<< orphan*/  SMD_EVENT_DATA ; 
 int /*<<< orphan*/  SMD_EVENT_OPEN ; 
 unsigned int SMD_SS_OPENED ; 
 int /*<<< orphan*/  notify_other_smd () ; 
 int /*<<< orphan*/  smd_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void smd_kick(smd_channel_t *ch)
{
	unsigned long flags;
	unsigned tmp;

	spin_lock_irqsave(&smd_lock, flags);
	ch->update_state(ch);
	tmp = ch->recv->state;
	if (tmp != ch->last_state) {
		ch->last_state = tmp;
		if (tmp == SMD_SS_OPENED)
			ch->notify(ch->priv, SMD_EVENT_OPEN);
		else
			ch->notify(ch->priv, SMD_EVENT_CLOSE);
	}
	ch->notify(ch->priv, SMD_EVENT_DATA);
	notify_other_smd();
	spin_unlock_irqrestore(&smd_lock, flags);
}