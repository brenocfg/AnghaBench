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
struct tty_struct {struct gs_port* driver_data; } ;
struct gs_port {int xmit_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 

int gs_chars_in_buffer(struct tty_struct *tty)
{
	struct gs_port *port = tty->driver_data;
	func_enter ();

	func_exit ();
	return port->xmit_cnt;
}