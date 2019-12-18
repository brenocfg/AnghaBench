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
struct edgeport_port {scalar_t__ ep_read_urb_state; int /*<<< orphan*/  ep_lock; int /*<<< orphan*/  shadow_mcr; } ;

/* Variables and functions */
 scalar_t__ EDGE_READ_URB_RUNNING ; 
 scalar_t__ EDGE_READ_URB_STOPPING ; 
 int /*<<< orphan*/  MCR_RTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void stop_read(struct edgeport_port *edge_port)
{
	unsigned long flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	if (edge_port->ep_read_urb_state == EDGE_READ_URB_RUNNING)
		edge_port->ep_read_urb_state = EDGE_READ_URB_STOPPING;
	edge_port->shadow_mcr &= ~MCR_RTS;

	spin_unlock_irqrestore(&edge_port->ep_lock, flags);
}