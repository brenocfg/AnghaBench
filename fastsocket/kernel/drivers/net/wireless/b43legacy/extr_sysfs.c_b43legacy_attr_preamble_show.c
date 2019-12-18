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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct b43legacy_wldev {TYPE_1__* wl; scalar_t__ short_preamble; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct b43legacy_wldev* dev_to_b43legacy_wldev (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t b43legacy_attr_preamble_show(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct b43legacy_wldev *wldev = dev_to_b43legacy_wldev(dev);
	ssize_t count;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	mutex_lock(&wldev->wl->mutex);

	if (wldev->short_preamble)
		count = snprintf(buf, PAGE_SIZE, "1 (Short Preamble"
				 " enabled)\n");
	else
		count = snprintf(buf, PAGE_SIZE, "0 (Short Preamble"
				 " disabled)\n");

	mutex_unlock(&wldev->wl->mutex);

	return count;
}