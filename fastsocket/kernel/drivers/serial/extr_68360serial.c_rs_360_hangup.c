#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct serial_state {scalar_t__ count; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tty; } ;
struct TYPE_6__ {int /*<<< orphan*/  open_wait; TYPE_1__ port; int /*<<< orphan*/  flags; scalar_t__ event; struct serial_state* state; } ;
typedef  TYPE_2__ ser_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  rs_360_flush_buffer (struct tty_struct*) ; 
 scalar_t__ serial_paranoia_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_360_hangup(struct tty_struct *tty)
{
	ser_info_t *info = (ser_info_t *)tty->driver_data;
	struct serial_state *state = info->state;
	
	if (serial_paranoia_check(info, tty->name, "rs_hangup"))
		return;

	state = info->state;
	
	rs_360_flush_buffer(tty);
	shutdown(info);
	info->event = 0;
	state->count = 0;
	info->flags &= ~ASYNC_NORMAL_ACTIVE;
	info->port.tty = NULL;
	wake_up_interruptible(&info->open_wait);
}