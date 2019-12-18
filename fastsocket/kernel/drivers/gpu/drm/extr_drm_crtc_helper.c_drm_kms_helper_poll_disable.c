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
struct TYPE_2__ {int /*<<< orphan*/  output_poll_slow_work; int /*<<< orphan*/  poll_enabled; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayed_slow_work_cancel (int /*<<< orphan*/ *) ; 

void drm_kms_helper_poll_disable(struct drm_device *dev)
{
	if (!dev->mode_config.poll_enabled)
		return;
	delayed_slow_work_cancel(&dev->mode_config.output_poll_slow_work);
}