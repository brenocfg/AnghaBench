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
struct usb_line6_variax {int model; int /*<<< orphan*/  line6; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ line6_send_program (int /*<<< orphan*/ *,int) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 
 struct usb_line6_variax* usb_get_intfdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t variax_set_model(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct usb_line6_variax *variax = usb_get_intfdata(to_usb_interface(dev));
	int value = simple_strtoul(buf, NULL, 10);

	if (line6_send_program(&variax->line6, value) == 0)
		variax->model = value;

	return count;
}