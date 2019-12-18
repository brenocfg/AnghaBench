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
struct tty_struct {TYPE_1__* termios; } ;
struct TYPE_2__ {int c_cflag; int c_ispeed; int c_ospeed; scalar_t__ c_iflag; scalar_t__ c_oflag; scalar_t__ c_lflag; } ;

/* Variables and functions */
 int B9600 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int CSTOPB ; 
 int PARENB ; 
 int TIOCM_CTS ; 
 TYPE_1__ tty_std_termios ; 

__attribute__((used)) static void iuu_init_termios(struct tty_struct *tty)
{
	*(tty->termios) = tty_std_termios;
	tty->termios->c_cflag = CLOCAL | CREAD | CS8 | B9600
				| TIOCM_CTS | CSTOPB | PARENB;
	tty->termios->c_ispeed = 9600;
	tty->termios->c_ospeed = 9600;
	tty->termios->c_lflag = 0;
	tty->termios->c_oflag = 0;
	tty->termios->c_iflag = 0;
}