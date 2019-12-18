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
struct iuu_private {int vcc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct usb_serial_port* to_usb_serial_port (struct device*) ; 
 struct iuu_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static ssize_t show_vcc_mode(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct usb_serial_port *port = to_usb_serial_port(dev);
	struct iuu_private *priv = usb_get_serial_port_data(port);

	return sprintf(buf, "%d\n", priv->vcc);
}