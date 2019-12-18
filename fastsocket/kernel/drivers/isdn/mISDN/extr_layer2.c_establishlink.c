#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_char ;
struct layer2 {int /*<<< orphan*/  flag; int /*<<< orphan*/  t203; scalar_t__ rc; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_PEND_REL ; 
 int SABM ; 
 int SABME ; 
 int /*<<< orphan*/  ST_L2_5 ; 
 int /*<<< orphan*/  clear_exception (struct layer2*) ; 
 int /*<<< orphan*/  freewin (struct layer2*) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  restart_t200 (struct layer2*,int) ; 
 int /*<<< orphan*/  send_uframe (struct layer2*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
establishlink(struct FsmInst *fi)
{
	struct layer2 *l2 = fi->userdata;
	u_char cmd;

	clear_exception(l2);
	l2->rc = 0;
	cmd = (test_bit(FLG_MOD128, &l2->flag) ? SABME : SABM) | 0x10;
	send_uframe(l2, NULL, cmd, CMD);
	mISDN_FsmDelTimer(&l2->t203, 1);
	restart_t200(l2, 1);
	test_and_clear_bit(FLG_PEND_REL, &l2->flag);
	freewin(l2);
	mISDN_FsmChangeState(fi, ST_L2_5);
}