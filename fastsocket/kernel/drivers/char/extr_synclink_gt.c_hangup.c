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
struct tty_struct {int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_wait; int /*<<< orphan*/ * tty; int /*<<< orphan*/  flags; scalar_t__ count; } ;
struct slgt_info {TYPE_1__ port; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int /*<<< orphan*/  flush_buffer (struct tty_struct*) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (struct slgt_info*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hangup(struct tty_struct *tty)
{
	struct slgt_info *info = tty->driver_data;

	if (sanity_check(info, tty->name, "hangup"))
		return;
	DBGINFO(("%s hangup\n", info->device_name));

	flush_buffer(tty);
	shutdown(info);

	info->port.count = 0;
	info->port.flags &= ~ASYNC_NORMAL_ACTIVE;
	info->port.tty = NULL;

	wake_up_interruptible(&info->port.open_wait);
}