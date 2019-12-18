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
struct usb_hub {int /*<<< orphan*/  intfdev; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
#define  HUB_LED_AMBER 131 
#define  HUB_LED_AUTO 130 
#define  HUB_LED_GREEN 129 
#define  HUB_LED_OFF 128 
 int /*<<< orphan*/  USB_PORT_FEAT_INDICATOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int set_port_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_port_led(
	struct usb_hub *hub,
	int port1,
	int selector
)
{
	int status = set_port_feature(hub->hdev, (selector << 8) | port1,
			USB_PORT_FEAT_INDICATOR);
	if (status < 0)
		dev_dbg (hub->intfdev,
			"port %d indicator %s status %d\n",
			port1,
			({ char *s; switch (selector) {
			case HUB_LED_AMBER: s = "amber"; break;
			case HUB_LED_GREEN: s = "green"; break;
			case HUB_LED_OFF: s = "off"; break;
			case HUB_LED_AUTO: s = "auto"; break;
			default: s = "??"; break;
			}; s; }),
			status);
}