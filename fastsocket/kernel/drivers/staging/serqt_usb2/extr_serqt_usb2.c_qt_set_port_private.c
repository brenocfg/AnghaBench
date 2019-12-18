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
struct usb_serial_port {int dummy; } ;
struct quatech_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,void*) ; 

__attribute__((used)) static inline void qt_set_port_private(struct usb_serial_port *port,
				       struct quatech_port *data)
{
	usb_set_serial_port_data(port, (void *)data);
}