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

/* Variables and functions */
 int /*<<< orphan*/  caleb_disable_rx (int) ; 
 int /*<<< orphan*/  caleb_disable_tx (int) ; 
 int /*<<< orphan*/  caleb_enable_rx (int) ; 
 int /*<<< orphan*/  pm3386_disable_rx (int) ; 
 int /*<<< orphan*/  pm3386_disable_tx (int) ; 
 int /*<<< orphan*/  pm3386_enable_rx (int) ; 
 int /*<<< orphan*/  pm3386_set_carrier (int,int) ; 

__attribute__((used)) static void enp2611_set_port_admin_status(int port, int up)
{
	if (up) {
		caleb_enable_rx(port);

		pm3386_set_carrier(port, 1);
		pm3386_enable_rx(port);
	} else {
		caleb_disable_tx(port);
		pm3386_disable_tx(port);
		/* @@@ Flush out pending packets.  */
		pm3386_set_carrier(port, 0);

		pm3386_disable_rx(port);
		caleb_disable_rx(port);
	}
}