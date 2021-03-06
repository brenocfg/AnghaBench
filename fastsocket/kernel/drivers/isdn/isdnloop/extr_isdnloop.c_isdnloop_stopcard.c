#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* statcallb ) (TYPE_3__*) ;} ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  isdnloop_lock; TYPE_1__ interface; int /*<<< orphan*/  myid; int /*<<< orphan*/ * c_timer; int /*<<< orphan*/  rb_timer; int /*<<< orphan*/  st_timer; } ;
typedef  TYPE_2__ isdnloop_card ;
struct TYPE_8__ {int /*<<< orphan*/  driver; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ isdn_ctrl ;

/* Variables and functions */
 int ISDNLOOP_FLAGS_RUNNING ; 
 int /*<<< orphan*/  ISDN_STAT_STOP ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
isdnloop_stopcard(isdnloop_card * card)
{
	unsigned long flags;
	isdn_ctrl cmd;

	spin_lock_irqsave(&card->isdnloop_lock, flags);
	if (card->flags & ISDNLOOP_FLAGS_RUNNING) {
		card->flags &= ~ISDNLOOP_FLAGS_RUNNING;
		del_timer(&card->st_timer);
		del_timer(&card->rb_timer);
		del_timer(&card->c_timer[0]);
		del_timer(&card->c_timer[1]);
		cmd.command = ISDN_STAT_STOP;
		cmd.driver = card->myid;
		card->interface.statcallb(&cmd);
	}
	spin_unlock_irqrestore(&card->isdnloop_lock, flags);
}