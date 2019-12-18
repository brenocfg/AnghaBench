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
struct TYPE_2__ {int /*<<< orphan*/  i_queue; int /*<<< orphan*/  t203; } ;
struct PStack {TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  INDICATION ; 
 int /*<<< orphan*/  RSP ; 
 int /*<<< orphan*/  ST_L2_4 ; 
 int UA ; 
 int /*<<< orphan*/  freewin (struct PStack*) ; 
 int get_PollFlagFree (struct PStack*,struct sk_buff*) ; 
 int /*<<< orphan*/  lapb_dl_release_l2l3 (struct PStack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_uframe (struct PStack*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct PStack*,int) ; 

__attribute__((used)) static void
l2_stop_multi(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;

	FsmChangeState(fi, ST_L2_4);
	FsmDelTimer(&st->l2.t203, 3);
	stop_t200(st, 4);

	send_uframe(st, UA | get_PollFlagFree(st, skb), RSP);

	skb_queue_purge(&st->l2.i_queue);
	freewin(st);
	lapb_dl_release_l2l3(st, INDICATION);
}