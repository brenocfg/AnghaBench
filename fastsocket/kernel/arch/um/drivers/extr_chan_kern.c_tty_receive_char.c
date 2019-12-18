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
struct tty_struct {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_IXOFF (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 char START_CHAR (struct tty_struct*) ; 
 char STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  start_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  stop_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tty_receive_char(struct tty_struct *tty, char ch)
{
	if (tty == NULL)
		return;

	if (I_IXON(tty) && !I_IXOFF(tty) && !tty->raw) {
		if (ch == STOP_CHAR(tty)) {
			stop_tty(tty);
			return;
		}
		else if (ch == START_CHAR(tty)) {
			start_tty(tty);
			return;
		}
	}

	tty_insert_flip_char(tty, ch, TTY_NORMAL);
}