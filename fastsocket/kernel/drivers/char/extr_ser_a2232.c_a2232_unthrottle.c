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
struct tty_struct {struct a2232_port* driver_data; } ;
struct a2232_port {scalar_t__ throttle_input; } ;

/* Variables and functions */

__attribute__((used)) static void a2232_unthrottle(struct tty_struct *tty)
{
/* Unthrottle: dual to "throttle()" above. */
	struct a2232_port *port = tty->driver_data;
	port->throttle_input = 0;
}