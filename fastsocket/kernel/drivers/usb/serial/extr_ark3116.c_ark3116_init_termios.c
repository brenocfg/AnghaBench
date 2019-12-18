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
struct tty_struct {struct ktermios* termios; } ;
struct ktermios {int c_cflag; int c_ispeed; int c_ospeed; } ;

/* Variables and functions */
 int B9600 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int HUPCL ; 
 struct ktermios tty_std_termios ; 

__attribute__((used)) static void ark3116_init_termios(struct tty_struct *tty)
{
	struct ktermios *termios = tty->termios;
	*termios = tty_std_termios;
	termios->c_cflag = B9600 | CS8
				      | CREAD | HUPCL | CLOCAL;
	termios->c_ispeed = 9600;
	termios->c_ospeed = 9600;
}