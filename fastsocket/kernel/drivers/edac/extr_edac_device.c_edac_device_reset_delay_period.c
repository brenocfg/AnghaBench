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
struct edac_device_ctl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_ctls_mutex ; 
 int /*<<< orphan*/  edac_device_workq_setup (struct edac_device_ctl_info*,unsigned long) ; 
 int /*<<< orphan*/  edac_device_workq_teardown (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void edac_device_reset_delay_period(struct edac_device_ctl_info *edac_dev,
					unsigned long value)
{
	/* cancel the current workq request, without the mutex lock */
	edac_device_workq_teardown(edac_dev);

	/* acquire the mutex before doing the workq setup */
	mutex_lock(&device_ctls_mutex);

	/* restart the workq request, with new delay value */
	edac_device_workq_setup(edac_dev, value);

	mutex_unlock(&device_ctls_mutex);
}