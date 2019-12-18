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
struct tty_struct {int /*<<< orphan*/  ldisc; int /*<<< orphan*/  flags; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_LDISC ; 
 struct tty_ldisc* get_ldisc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_ldisc_lock ; 

__attribute__((used)) static struct tty_ldisc *tty_ldisc_try(struct tty_struct *tty)
{
	unsigned long flags;
	struct tty_ldisc *ld;

	spin_lock_irqsave(&tty_ldisc_lock, flags);
	ld = NULL;
	if (test_bit(TTY_LDISC, &tty->flags))
		ld = get_ldisc(tty->ldisc);
	spin_unlock_irqrestore(&tty_ldisc_lock, flags);
	return ld;
}