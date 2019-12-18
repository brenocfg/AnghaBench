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
struct edac_device_ctl_info {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_workqueue ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

void edac_device_workq_teardown(struct edac_device_ctl_info *edac_dev)
{
	int status;

	status = cancel_delayed_work(&edac_dev->work);
	if (status == 0) {
		/* workq instance might be running, wait for it */
		flush_workqueue(edac_workqueue);
	}
}