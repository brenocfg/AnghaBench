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
struct wusbhc {unsigned int trust_timeout; int /*<<< orphan*/  keep_alive_timer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int CONFIG_HZ ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 struct wusbhc* usbhc_dev_to_wusbhc (struct device*) ; 
 int /*<<< orphan*/  wusbd ; 

__attribute__((used)) static ssize_t wusb_trust_timeout_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t size)
{
	struct wusbhc *wusbhc = usbhc_dev_to_wusbhc(dev);
	ssize_t result = -ENOSYS;
	unsigned trust_timeout;

	result = sscanf(buf, "%u", &trust_timeout);
	if (result != 1) {
		result = -EINVAL;
		goto out;
	}
	/* FIXME: maybe we should check for range validity? */
	wusbhc->trust_timeout = trust_timeout;
	cancel_delayed_work(&wusbhc->keep_alive_timer);
	flush_workqueue(wusbd);
	queue_delayed_work(wusbd, &wusbhc->keep_alive_timer,
			   (trust_timeout * CONFIG_HZ)/1000/2);
out:
	return result < 0 ? result : size;
}