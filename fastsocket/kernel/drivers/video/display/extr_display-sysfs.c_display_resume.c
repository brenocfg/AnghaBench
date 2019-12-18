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
struct display_device {int /*<<< orphan*/  lock; TYPE_1__* driver; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct display_device*) ;} ;

/* Variables and functions */
 struct display_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (struct display_device*)) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct display_device*) ; 

__attribute__((used)) static int display_resume(struct device *dev)
{
	struct display_device *dsp = dev_get_drvdata(dev);

	mutex_lock(&dsp->lock);
	if (likely(dsp->driver->resume))
		dsp->driver->resume(dsp);
	mutex_unlock(&dsp->lock);
	return 0;
}