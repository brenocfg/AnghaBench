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
struct port {int /*<<< orphan*/  guest_connected; int /*<<< orphan*/  waitqueue; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int wait_event_freezable (int /*<<< orphan*/ ,int) ; 
 scalar_t__ will_write_block (struct port*) ; 

__attribute__((used)) static int wait_port_writable(struct port *port, bool nonblock)
{
	int ret;

	if (will_write_block(port)) {
		if (nonblock)
			return -EAGAIN;

		ret = wait_event_freezable(port->waitqueue,
					   !will_write_block(port));
		if (ret < 0)
			return ret;
	}
	/* Port got hot-unplugged. */
	if (!port->guest_connected)
		return -ENODEV;

	return 0;
}