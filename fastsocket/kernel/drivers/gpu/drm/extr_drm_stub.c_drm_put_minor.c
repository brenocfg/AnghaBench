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
struct drm_minor {scalar_t__ type; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_MINOR_LEGACY ; 
 int /*<<< orphan*/  drm_debugfs_cleanup (struct drm_minor*) ; 
 int /*<<< orphan*/  drm_minors_idr ; 
 int /*<<< orphan*/  drm_proc_cleanup (struct drm_minor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_proc_root ; 
 int /*<<< orphan*/  drm_sysfs_device_remove (struct drm_minor*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_minor*) ; 

int drm_put_minor(struct drm_minor **minor_p)
{
	struct drm_minor *minor = *minor_p;

	DRM_DEBUG("release secondary minor %d\n", minor->index);

	if (minor->type == DRM_MINOR_LEGACY)
		drm_proc_cleanup(minor, drm_proc_root);
#if defined(CONFIG_DEBUG_FS)
	drm_debugfs_cleanup(minor);
#endif

	drm_sysfs_device_remove(minor);

	idr_remove(&drm_minors_idr, minor->index);

	kfree(minor);
	*minor_p = NULL;
	return 0;
}