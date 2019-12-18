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
struct smsusb_device_t {int /*<<< orphan*/ * surbs; } ;

/* Variables and functions */
 int MAX_URBS ; 
 int /*<<< orphan*/  sms_err (char*) ; 
 int /*<<< orphan*/  smsusb_stop_streaming (struct smsusb_device_t*) ; 
 int smsusb_submit_urb (struct smsusb_device_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsusb_start_streaming(struct smsusb_device_t *dev)
{
	int i, rc;

	for (i = 0; i < MAX_URBS; i++) {
		rc = smsusb_submit_urb(dev, &dev->surbs[i]);
		if (rc < 0) {
			sms_err("smsusb_submit_urb(...) failed");
			smsusb_stop_streaming(dev);
			break;
		}
	}

	return rc;
}