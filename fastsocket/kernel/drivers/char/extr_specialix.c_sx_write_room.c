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
struct tty_struct {int /*<<< orphan*/  name; struct specialix_port* driver_data; } ;
struct specialix_port {int xmit_cnt; } ;

/* Variables and functions */
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 scalar_t__ sx_paranoia_check (struct specialix_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sx_write_room(struct tty_struct *tty)
{
	struct specialix_port *port = tty->driver_data;
	int	ret;

	func_enter();

	if (sx_paranoia_check(port, tty->name, "sx_write_room")) {
		func_exit();
		return 0;
	}

	ret = SERIAL_XMIT_SIZE - port->xmit_cnt - 1;
	if (ret < 0)
		ret = 0;

	func_exit();
	return ret;
}