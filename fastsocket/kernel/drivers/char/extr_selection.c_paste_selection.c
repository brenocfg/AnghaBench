#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int /*<<< orphan*/  paste_wait; } ;
struct tty_struct {TYPE_2__* ldisc; int /*<<< orphan*/  receive_room; int /*<<< orphan*/  flags; struct vc_data* driver_data; } ;
struct tty_ldisc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* receive_buf ) (struct tty_struct*,scalar_t__,int /*<<< orphan*/ *,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TTY_THROTTLED ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke_blanked_console () ; 
 int /*<<< orphan*/  release_console_sem () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ sel_buffer ; 
 int sel_buffer_lth ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref_wait (struct tty_struct*) ; 
 int /*<<< orphan*/  wait ; 

int paste_selection(struct tty_struct *tty)
{
	struct vc_data *vc = tty->driver_data;
	int	pasted = 0;
	unsigned int count;
	struct  tty_ldisc *ld;
	DECLARE_WAITQUEUE(wait, current);

	acquire_console_sem();
	poke_blanked_console();
	release_console_sem();

	ld = tty_ldisc_ref_wait(tty);
	
	add_wait_queue(&vc->paste_wait, &wait);
	while (sel_buffer && sel_buffer_lth > pasted) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (test_bit(TTY_THROTTLED, &tty->flags)) {
			schedule();
			continue;
		}
		count = sel_buffer_lth - pasted;
		count = min(count, tty->receive_room);
		tty->ldisc->ops->receive_buf(tty, sel_buffer + pasted,
								NULL, count);
		pasted += count;
	}
	remove_wait_queue(&vc->paste_wait, &wait);
	__set_current_state(TASK_RUNNING);

	tty_ldisc_deref(ld);
	return 0;
}