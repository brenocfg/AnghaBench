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
struct wusb_port {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_STAT_HIGH_SPEED ; 

__attribute__((used)) static void wusb_port_init(struct wusb_port *port)
{
	port->status |= USB_PORT_STAT_HIGH_SPEED;
}