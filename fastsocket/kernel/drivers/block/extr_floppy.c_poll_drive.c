#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int flags; scalar_t__ cmd_count; scalar_t__ track; } ;

/* Variables and functions */
 TYPE_3__* DP ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int FD_DEBUG ; 
 int /*<<< orphan*/  FD_DISK_NEWCHANGE ; 
 int /*<<< orphan*/  SETF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cont ; 
 TYPE_1__ default_raw_cmd ; 
 int /*<<< orphan*/  floppy_ready ; 
 int /*<<< orphan*/  poll_cont ; 
 TYPE_1__* raw_cmd ; 

__attribute__((used)) static int poll_drive(int interruptible, int flag)
{
	int ret;

	/* no auto-sense, just clear dcl */
	raw_cmd = &default_raw_cmd;
	raw_cmd->flags = flag;
	raw_cmd->track = 0;
	raw_cmd->cmd_count = 0;
	cont = &poll_cont;
#ifdef DCL_DEBUG
	if (DP->flags & FD_DEBUG) {
		DPRINT("setting NEWCHANGE in poll_drive\n");
	}
#endif
	SETF(FD_DISK_NEWCHANGE);
	WAIT(floppy_ready);
	return ret;
}