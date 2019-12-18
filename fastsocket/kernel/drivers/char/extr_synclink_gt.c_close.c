#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* driver; int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  count; int /*<<< orphan*/ * tty; } ;
struct slgt_info {TYPE_2__ port; int /*<<< orphan*/  timeout; int /*<<< orphan*/  device_name; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int /*<<< orphan*/  flush_buffer (struct tty_struct*) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (struct slgt_info*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (TYPE_2__*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (TYPE_2__*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close(struct tty_struct *tty, struct file *filp)
{
	struct slgt_info *info = tty->driver_data;

	if (sanity_check(info, tty->name, "close"))
		return;
	DBGINFO(("%s close entry, count=%d\n", info->device_name, info->port.count));

	if (tty_port_close_start(&info->port, tty, filp) == 0)
		goto cleanup;

 	if (info->port.flags & ASYNC_INITIALIZED)
 		wait_until_sent(tty, info->timeout);
	flush_buffer(tty);
	tty_ldisc_flush(tty);

	shutdown(info);

	tty_port_close_end(&info->port, tty);
	info->port.tty = NULL;
cleanup:
	DBGINFO(("%s close exit, count=%d\n", tty->driver->name, info->port.count));
}