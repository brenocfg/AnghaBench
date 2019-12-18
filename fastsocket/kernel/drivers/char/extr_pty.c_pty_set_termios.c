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
struct ktermios {int dummy; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CREAD ; 
 int CS8 ; 
 int CSIZE ; 
 int PARENB ; 

__attribute__((used)) static void pty_set_termios(struct tty_struct *tty,
					struct ktermios *old_termios)
{
	tty->termios->c_cflag &= ~(CSIZE | PARENB);
	tty->termios->c_cflag |= (CS8 | CREAD);
}