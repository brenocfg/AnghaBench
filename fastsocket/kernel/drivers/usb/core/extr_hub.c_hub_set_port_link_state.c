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
struct usb_hub {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_FEAT_LINK_STATE ; 
 int set_port_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hub_set_port_link_state(struct usb_hub *hub, int port1,
			unsigned int link_status)
{
	return set_port_feature(hub->hdev,
			port1 | (link_status << 3),
			USB_PORT_FEAT_LINK_STATE);
}