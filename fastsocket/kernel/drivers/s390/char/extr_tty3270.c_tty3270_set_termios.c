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
struct tty_struct {struct tty3270* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct tty3270 {int inattr; TYPE_1__ view; } ;
struct ktermios {int dummy; } ;

/* Variables and functions */
 scalar_t__ L_ECHO (struct tty_struct*) ; 
 scalar_t__ L_ICANON (struct tty_struct*) ; 
 int TF_INPUT ; 
 int TF_INPUTN ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty3270_set_timer (struct tty3270*,int) ; 
 int /*<<< orphan*/  tty3270_update_prompt (struct tty3270*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tty3270_set_termios(struct tty_struct *tty, struct ktermios *old)
{
	struct tty3270 *tp;
	int new;

	tp = tty->driver_data;
	if (!tp)
		return;
	spin_lock_bh(&tp->view.lock);
	if (L_ICANON(tty)) {
		new = L_ECHO(tty) ? TF_INPUT: TF_INPUTN;
		if (new != tp->inattr) {
			tp->inattr = new;
			tty3270_update_prompt(tp, NULL, 0);
			tty3270_set_timer(tp, 1);
		}
	}
	spin_unlock_bh(&tp->view.lock);
}