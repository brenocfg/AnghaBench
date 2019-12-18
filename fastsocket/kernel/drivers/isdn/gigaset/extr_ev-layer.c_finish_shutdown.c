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
struct cardstate {scalar_t__ mstate; int /*<<< orphan*/  waitqueue; scalar_t__ waiting; int /*<<< orphan*/  cmd_result; scalar_t__ isdn_up; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ISDN_STAT_STOP ; 
 scalar_t__ MS_LOCKED ; 
 scalar_t__ MS_UNINITIALIZED ; 
 int /*<<< orphan*/  M_UNKNOWN ; 
 int /*<<< orphan*/  gigaset_i4l_cmd (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void finish_shutdown(struct cardstate *cs)
{
	if (cs->mstate != MS_LOCKED) {
		cs->mstate = MS_UNINITIALIZED;
		cs->mode = M_UNKNOWN;
	}

	/* Tell the LL that the device is not available .. */
	if (cs->isdn_up) {
		cs->isdn_up = 0;
		gigaset_i4l_cmd(cs, ISDN_STAT_STOP);
	}

	/* The rest is done by cleanup_cs () in user mode. */

	cs->cmd_result = -ENODEV;
	cs->waiting = 0;
	wake_up(&cs->waitqueue);
}