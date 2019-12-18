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
struct tty_struct {scalar_t__ driver_data; } ;
struct serial_state {scalar_t__ count; } ;
struct async_struct {int flags; int /*<<< orphan*/  open_wait; int /*<<< orphan*/ * tty; scalar_t__ event; struct serial_state* state; } ;

/* Variables and functions */
 int ASYNC_CLOSING ; 
 int ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  rs_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  shutdown (struct async_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_hangup(struct tty_struct *tty)
{
	struct async_struct * info = (struct async_struct *)tty->driver_data;
	struct serial_state *state = info->state;

#ifdef SIMSERIAL_DEBUG
	printk("rs_hangup: called\n");
#endif

	state = info->state;

	rs_flush_buffer(tty);
	if (info->flags & ASYNC_CLOSING)
		return;
	shutdown(info);

	info->event = 0;
	state->count = 0;
	info->flags &= ~ASYNC_NORMAL_ACTIVE;
	info->tty = NULL;
	wake_up_interruptible(&info->open_wait);
}