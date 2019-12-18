#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct airo_info {int flags; int /*<<< orphan*/  bssListRidLen; int /*<<< orphan*/  bssListNext; int /*<<< orphan*/  bssListFirst; int /*<<< orphan*/ * list_bss_task; int /*<<< orphan*/  sem; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  Resp ;
typedef  TYPE_1__ Cmd ;
typedef  int /*<<< orphan*/  BSSListRid ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_LISTBSS ; 
 int ENETDOWN ; 
 int ERESTARTSYS ; 
 int FLAG_RADIO_MASK ; 
 int HZ ; 
 int PC4500_readrid (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * current ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issuecommand (struct airo_info*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int readBSSListRid(struct airo_info *ai, int first,
		      BSSListRid *list)
{
	Cmd cmd;
	Resp rsp;

	if (first == 1) {
		if (ai->flags & FLAG_RADIO_MASK) return -ENETDOWN;
		memset(&cmd, 0, sizeof(cmd));
		cmd.cmd=CMD_LISTBSS;
		if (down_interruptible(&ai->sem))
			return -ERESTARTSYS;
		ai->list_bss_task = current;
		issuecommand(ai, &cmd, &rsp);
		up(&ai->sem);
		/* Let the command take effect */
		schedule_timeout_uninterruptible(3 * HZ);
		ai->list_bss_task = NULL;
	}
	return PC4500_readrid(ai, first ? ai->bssListFirst : ai->bssListNext,
			    list, ai->bssListRidLen, 1);
}