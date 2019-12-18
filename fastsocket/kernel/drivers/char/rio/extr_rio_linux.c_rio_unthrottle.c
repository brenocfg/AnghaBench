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
struct tty_struct {scalar_t__ driver_data; } ;
struct Port {int /*<<< orphan*/  State; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_THROTTLE_RX ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 

__attribute__((used)) static void rio_unthrottle(struct tty_struct *tty)
{
	struct Port *port = (struct Port *) tty->driver_data;

	func_enter();
	/* Always unthrottle even if flow control is not enabled on
	 * this port in case we disabled flow control while the port
	 * was throttled
	 */

	port->State &= ~RIO_THROTTLE_RX;

	func_exit();
	return;
}