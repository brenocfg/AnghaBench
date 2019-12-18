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
struct display_device {int /*<<< orphan*/  idx; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_dsp ; 
 int /*<<< orphan*/  allocated_dsp_lock ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct display_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void display_device_unregister(struct display_device *ddev)
{
	if (!ddev)
		return;
	// Free device
	mutex_lock(&ddev->lock);
	device_unregister(ddev->dev);
	mutex_unlock(&ddev->lock);
	// Mark device index as avaliable
	mutex_lock(&allocated_dsp_lock);
	idr_remove(&allocated_dsp, ddev->idx);
	mutex_unlock(&allocated_dsp_lock);
	kfree(ddev);
}