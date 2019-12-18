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
struct ctlr_info {int /*<<< orphan*/  scan_wait; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_scan_list (struct ctlr_info*) ; 
 int /*<<< orphan*/  cciss_scan_thread ; 
 struct ctlr_info* to_hba (struct device*) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t host_store_rescan(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct ctlr_info *h = to_hba(dev);

	add_to_scan_list(h);
	wake_up_process(cciss_scan_thread);
	wait_for_completion_interruptible(&h->scan_wait);

	return count;
}