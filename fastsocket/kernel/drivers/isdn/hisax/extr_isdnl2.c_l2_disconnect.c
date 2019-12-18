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
struct TYPE_2__ {int /*<<< orphan*/  t203; scalar_t__ rc; int /*<<< orphan*/  i_queue; } ;
struct PStack {TYPE_1__ l2; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int DISC ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_L2_6 ; 
 int /*<<< orphan*/  freewin (struct PStack*) ; 
 int /*<<< orphan*/  restart_t200 (struct PStack*,int) ; 
 int /*<<< orphan*/  send_uframe (struct PStack*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_disconnect(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;

	skb_queue_purge(&st->l2.i_queue);
	freewin(st);
	FsmChangeState(fi, ST_L2_6);
	st->l2.rc = 0;
	send_uframe(st, DISC | 0x10, CMD);
	FsmDelTimer(&st->l2.t203, 1);
	restart_t200(st, 2);
}