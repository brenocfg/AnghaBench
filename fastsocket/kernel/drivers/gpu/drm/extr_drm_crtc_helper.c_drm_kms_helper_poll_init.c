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
struct TYPE_2__ {int poll_enabled; int /*<<< orphan*/  output_poll_slow_work; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  delayed_slow_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 int /*<<< orphan*/  output_poll_ops ; 
 int /*<<< orphan*/  slow_work_register_user (int /*<<< orphan*/ ) ; 

void drm_kms_helper_poll_init(struct drm_device *dev)
{
	slow_work_register_user(THIS_MODULE);
	delayed_slow_work_init(&dev->mode_config.output_poll_slow_work,
			       &output_poll_ops);
	dev->mode_config.poll_enabled = true;

	drm_kms_helper_poll_enable(dev);
}