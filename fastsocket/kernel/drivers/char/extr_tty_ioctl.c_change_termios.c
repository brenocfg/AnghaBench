#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int ctrl_status; int /*<<< orphan*/  termios_mutex; struct ktermios* termios; TYPE_2__* ops; TYPE_1__* link; int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/  termios_locked; } ;
struct tty_ldisc {TYPE_3__* ops; } ;
struct ktermios {int c_iflag; char* c_cc; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct ktermios*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct ktermios*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  read_wait; scalar_t__ packet; } ;

/* Variables and functions */
 int IXON ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 char START_CHAR (struct tty_struct*) ; 
 char STOP_CHAR (struct tty_struct*) ; 
 int TIOCPKT_DOSTOP ; 
 int TIOCPKT_NOSTOP ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_termios_copy_hw (struct ktermios*,struct ktermios*) ; 
 int /*<<< orphan*/  unset_locked_termios (struct ktermios*,struct ktermios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void change_termios(struct tty_struct *tty, struct ktermios *new_termios)
{
	struct ktermios old_termios;
	struct tty_ldisc *ld;
	unsigned long flags;

	/*
	 *	Perform the actual termios internal changes under lock.
	 */


	/* FIXME: we need to decide on some locking/ordering semantics
	   for the set_termios notification eventually */
	mutex_lock(&tty->termios_mutex);
	old_termios = *tty->termios;
	*tty->termios = *new_termios;
	unset_locked_termios(tty->termios, &old_termios, tty->termios_locked);

	/* See if packet mode change of state. */
	if (tty->link && tty->link->packet) {
		int old_flow = ((old_termios.c_iflag & IXON) &&
				(old_termios.c_cc[VSTOP] == '\023') &&
				(old_termios.c_cc[VSTART] == '\021'));
		int new_flow = (I_IXON(tty) &&
				STOP_CHAR(tty) == '\023' &&
				START_CHAR(tty) == '\021');
		if (old_flow != new_flow) {
			spin_lock_irqsave(&tty->ctrl_lock, flags);
			tty->ctrl_status &= ~(TIOCPKT_DOSTOP | TIOCPKT_NOSTOP);
			if (new_flow)
				tty->ctrl_status |= TIOCPKT_DOSTOP;
			else
				tty->ctrl_status |= TIOCPKT_NOSTOP;
			spin_unlock_irqrestore(&tty->ctrl_lock, flags);
			wake_up_interruptible(&tty->link->read_wait);
		}
	}

	if (tty->ops->set_termios)
		(*tty->ops->set_termios)(tty, &old_termios);
	else
		tty_termios_copy_hw(tty->termios, &old_termios);

	ld = tty_ldisc_ref(tty);
	if (ld != NULL) {
		if (ld->ops->set_termios)
			(ld->ops->set_termios)(tty, &old_termios);
		tty_ldisc_deref(ld);
	}
	mutex_unlock(&tty->termios_mutex);
}