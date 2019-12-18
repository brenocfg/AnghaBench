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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* l2l1 ) (struct PStack*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  flag; int /*<<< orphan*/  i_queue; } ;
struct PStack {TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L3_INIT ; 
 int /*<<< orphan*/  FLG_LAPB ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int PH_DEACTIVATE ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 scalar_t__ get_PollFlagFree (struct PStack*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st5_dl_release_l2l3 (struct PStack*) ; 
 int /*<<< orphan*/  stop_t200 (struct PStack*,int) ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_st5_dm_release(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	if (get_PollFlagFree(st, skb)) {
		stop_t200(st, 7);
	 	if (!test_bit(FLG_L3_INIT, &st->l2.flag))
			skb_queue_purge(&st->l2.i_queue);
		if (test_bit(FLG_LAPB, &st->l2.flag))
			st->l2.l2l1(st, PH_DEACTIVATE | REQUEST, NULL);
		st5_dl_release_l2l3(st);
		FsmChangeState(fi, ST_L2_4);
	}
}