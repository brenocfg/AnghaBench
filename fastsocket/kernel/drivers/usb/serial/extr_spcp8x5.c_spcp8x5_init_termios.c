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
struct TYPE_2__ {int c_cflag; int c_ispeed; int c_ospeed; } ;

/* Variables and functions */
 int B115200 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int HUPCL ; 
 TYPE_1__ tty_std_termios ; 

__attribute__((used)) static void spcp8x5_init_termios(struct tty_struct *tty)
{
	/* for the 1st time call this function */
	*(tty->termios) = tty_std_termios;
	tty->termios->c_cflag = B115200 | CS8 | CREAD | HUPCL | CLOCAL;
	tty->termios->c_ispeed = 115200;
	tty->termios->c_ospeed = 115200;
}