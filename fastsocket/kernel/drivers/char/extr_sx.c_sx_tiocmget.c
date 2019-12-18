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
struct tty_struct {struct sx_port* driver_data; } ;
struct sx_port {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int sx_getsignals (struct sx_port*) ; 

__attribute__((used)) static int sx_tiocmget(struct tty_struct *tty, struct file *file)
{
	struct sx_port *port = tty->driver_data;
	return sx_getsignals(port);
}