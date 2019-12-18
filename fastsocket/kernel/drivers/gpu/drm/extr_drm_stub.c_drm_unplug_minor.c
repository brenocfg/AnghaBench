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
struct drm_minor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sysfs_device_remove (struct drm_minor*) ; 

__attribute__((used)) static void drm_unplug_minor(struct drm_minor *minor)
{
	drm_sysfs_device_remove(minor);
}