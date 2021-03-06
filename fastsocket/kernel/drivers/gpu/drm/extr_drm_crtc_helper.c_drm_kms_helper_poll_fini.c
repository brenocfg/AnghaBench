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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  slow_work_unregister_user (int /*<<< orphan*/ ) ; 

void drm_kms_helper_poll_fini(struct drm_device *dev)
{
	drm_kms_helper_poll_disable(dev);
	slow_work_unregister_user(THIS_MODULE);
}