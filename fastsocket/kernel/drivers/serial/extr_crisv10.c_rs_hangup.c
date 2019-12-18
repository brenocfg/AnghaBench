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
struct tty_struct {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tty; } ;
struct e100_serial {int /*<<< orphan*/  open_wait; TYPE_1__ port; int /*<<< orphan*/  flags; scalar_t__ count; scalar_t__ event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  rs_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  shutdown (struct e100_serial*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void
rs_hangup(struct tty_struct *tty)
{
	struct e100_serial * info = (struct e100_serial *)tty->driver_data;

	rs_flush_buffer(tty);
	shutdown(info);
	info->event = 0;
	info->count = 0;
	info->flags &= ~ASYNC_NORMAL_ACTIVE;
	info->port.tty = NULL;
	wake_up_interruptible(&info->open_wait);
}