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
struct usb_line6_pod {int /*<<< orphan*/  line6; } ;
struct usb_interface {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  POD_SYSEX_FINISH ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  line6_send_sysex_message (int /*<<< orphan*/ *,char*,int) ; 
 char* pod_alloc_sysex_buffer (struct usb_line6_pod*,int /*<<< orphan*/ ,int) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_line6_pod* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t pod_set_finish(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct usb_interface *interface = to_usb_interface(dev);
	struct usb_line6_pod *pod = usb_get_intfdata(interface);
	int size = 0;
	char *sysex = pod_alloc_sysex_buffer(pod, POD_SYSEX_FINISH, size);
	if (!sysex)
		return 0;
	line6_send_sysex_message(&pod->line6, sysex, size);
	kfree(sysex);
	return count;
}