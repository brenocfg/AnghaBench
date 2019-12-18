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
struct uvc_device {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_TRACE_STATUS ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void uvc_event_control(struct uvc_device *dev, __u8 *data, int len)
{
	char *attrs[3] = { "value", "info", "failure" };

	if (len < 6 || data[2] != 0 || data[4] > 2) {
		uvc_trace(UVC_TRACE_STATUS, "Invalid control status event "
				"received.\n");
		return;
	}

	uvc_trace(UVC_TRACE_STATUS, "Control %u/%u %s change len %d.\n",
		data[1], data[3], attrs[data[4]], len);
}