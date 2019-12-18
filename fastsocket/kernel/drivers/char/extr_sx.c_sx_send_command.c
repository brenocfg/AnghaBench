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
struct sx_port {int /*<<< orphan*/  board; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_OFFSET (struct sx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_enter2 () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  hi_hstat ; 
 int sx_busy_wait_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_sx_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sx_send_command(struct sx_port *port,
		int command, int mask, int newstat)
{
	func_enter2();
	write_sx_byte(port->board, CHAN_OFFSET(port, hi_hstat), command);
	func_exit();
	return sx_busy_wait_eq(port->board, CHAN_OFFSET(port, hi_hstat), mask,
			newstat);
}