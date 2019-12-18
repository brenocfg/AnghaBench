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
struct winsize {int dummy; } ;
struct tty_struct {int /*<<< orphan*/  termios_mutex; struct winsize winsize; int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/  pgrp; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGWINCH ; 
 struct pid* get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_pgrp (struct pid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (struct winsize*,struct winsize*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int tty_do_resize(struct tty_struct *tty, struct winsize *ws)
{
	struct pid *pgrp;
	unsigned long flags;

	/* Lock the tty */
	mutex_lock(&tty->termios_mutex);
	if (!memcmp(ws, &tty->winsize, sizeof(*ws)))
		goto done;
	/* Get the PID values and reference them so we can
	   avoid holding the tty ctrl lock while sending signals */
	spin_lock_irqsave(&tty->ctrl_lock, flags);
	pgrp = get_pid(tty->pgrp);
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);

	if (pgrp)
		kill_pgrp(pgrp, SIGWINCH, 1);
	put_pid(pgrp);

	tty->winsize = *ws;
done:
	mutex_unlock(&tty->termios_mutex);
	return 0;
}