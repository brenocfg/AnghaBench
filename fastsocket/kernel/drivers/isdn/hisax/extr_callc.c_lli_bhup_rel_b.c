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
struct FsmInst {struct Channel* userdata; } ;
struct Channel {int debug; scalar_t__ data_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HL_LL (struct Channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISDN_STAT_BHUP ; 
 int /*<<< orphan*/  ST_WAIT_DCOMMAND ; 
 int /*<<< orphan*/  link_debug (struct Channel*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  release_b_st (struct Channel*) ; 

__attribute__((used)) static void
lli_bhup_rel_b(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	FsmChangeState(fi, ST_WAIT_DCOMMAND);
	chanp->data_open = 0;
	if (chanp->debug & 1)
		link_debug(chanp, 0, "STAT_BHUP");
	HL_LL(chanp, ISDN_STAT_BHUP);
	release_b_st(chanp);
}