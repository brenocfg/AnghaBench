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
struct tty_struct {int stopped; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct tty_struct*,char*,int) ;int /*<<< orphan*/  (* send_xchar ) (struct tty_struct*,char) ;} ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  start_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  stop_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,char) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*,char*,int) ; 
 scalar_t__ tty_write_lock (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_write_unlock (struct tty_struct*) ; 

__attribute__((used)) static int send_prio_char(struct tty_struct *tty, char ch)
{
	int	was_stopped = tty->stopped;

	if (tty->ops->send_xchar) {
		tty->ops->send_xchar(tty, ch);
		return 0;
	}

	if (tty_write_lock(tty, 0) < 0)
		return -ERESTARTSYS;

	if (was_stopped)
		start_tty(tty);
	tty->ops->write(tty, &ch, 1);
	if (was_stopped)
		stop_tty(tty);
	tty_write_unlock(tty);
	return 0;
}