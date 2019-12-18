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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ap_device {int pendingq_count; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_device* to_ap_dev (struct device*) ; 

__attribute__((used)) static ssize_t ap_pendingq_count_show(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct ap_device *ap_dev = to_ap_dev(dev);
	int rc;

	spin_lock_bh(&ap_dev->lock);
	rc = snprintf(buf, PAGE_SIZE, "%d\n", ap_dev->pendingq_count);
	spin_unlock_bh(&ap_dev->lock);
	return rc;
}