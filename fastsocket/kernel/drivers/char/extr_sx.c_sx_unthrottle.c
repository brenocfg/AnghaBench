#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct sx_port* driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ port; } ;
struct sx_port {TYPE_2__ gs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX_RX_THROTTLE ; 
 int /*<<< orphan*/  func_enter2 () ; 
 int /*<<< orphan*/  func_exit () ; 

__attribute__((used)) static void sx_unthrottle(struct tty_struct *tty)
{
	struct sx_port *port = tty->driver_data;

	func_enter2();
	/* Always unthrottle even if flow control is not enabled on
	 * this port in case we disabled flow control while the port
	 * was throttled
	 */
	port->gs.port.flags &= ~SX_RX_THROTTLE;
	func_exit();
	return;
}