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
struct teimgr {TYPE_1__* mgr; int /*<<< orphan*/  timer; } ;
struct layer2 {struct teimgr* tm; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct teimgr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
TEIrelease(struct layer2 *l2)
{
	struct teimgr	*tm = l2->tm;
	u_long		flags;

	mISDN_FsmDelTimer(&tm->timer, 1);
	write_lock_irqsave(&tm->mgr->lock, flags);
	list_del(&l2->list);
	write_unlock_irqrestore(&tm->mgr->lock, flags);
	l2->tm = NULL;
	kfree(tm);
}