#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_line6 {TYPE_1__* line6midi; } ;
struct usb_interface {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int midi_mask_transmit; } ;

/* Variables and functions */
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_line6* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t midi_set_midi_mask_transmit(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t count)
{
	struct usb_interface *interface = to_usb_interface(dev);
	struct usb_line6 *line6 = usb_get_intfdata(interface);
	int value = simple_strtoul(buf, NULL, 10);
	line6->line6midi->midi_mask_transmit = value;
	return count;
}