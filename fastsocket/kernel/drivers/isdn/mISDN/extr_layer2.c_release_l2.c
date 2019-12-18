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
struct TYPE_7__ {TYPE_2__* st; } ;
struct layer2 {TYPE_3__ ch; int /*<<< orphan*/  flag; int /*<<< orphan*/  down_queue; int /*<<< orphan*/  ui_queue; int /*<<< orphan*/  i_queue; int /*<<< orphan*/  t203; int /*<<< orphan*/  t200; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* ctrl ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_5__ {TYPE_4__ D; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_CHANNEL ; 
 int /*<<< orphan*/  FLG_LAPD ; 
 int /*<<< orphan*/  ReleaseWin (struct layer2*) ; 
 int /*<<< orphan*/  TEIrelease (struct layer2*) ; 
 int /*<<< orphan*/  kfree (struct layer2*) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
release_l2(struct layer2 *l2)
{
	mISDN_FsmDelTimer(&l2->t200, 21);
	mISDN_FsmDelTimer(&l2->t203, 16);
	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	skb_queue_purge(&l2->down_queue);
	ReleaseWin(l2);
	if (test_bit(FLG_LAPD, &l2->flag)) {
		TEIrelease(l2);
		if (l2->ch.st)
			l2->ch.st->dev->D.ctrl(&l2->ch.st->dev->D,
			    CLOSE_CHANNEL, NULL);
	}
	kfree(l2);
}