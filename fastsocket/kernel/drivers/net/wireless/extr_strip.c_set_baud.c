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
struct tty_struct {int /*<<< orphan*/  termios_mutex; TYPE_1__* ops; struct ktermios* termios; } ;
struct ktermios {int dummy; } ;
typedef  int /*<<< orphan*/  speed_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct ktermios*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_baud(struct tty_struct *tty, speed_t baudrate)
{
	struct ktermios old_termios;

	mutex_lock(&tty->termios_mutex);
	old_termios =*(tty->termios);
	tty_encode_baud_rate(tty, baudrate, baudrate);
	tty->ops->set_termios(tty, &old_termios);
	mutex_unlock(&tty->termios_mutex);
}