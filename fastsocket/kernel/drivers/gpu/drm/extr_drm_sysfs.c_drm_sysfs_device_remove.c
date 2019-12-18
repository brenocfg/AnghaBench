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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct drm_minor {TYPE_1__ kdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 

void drm_sysfs_device_remove(struct drm_minor *minor)
{
	if (minor->kdev.parent)
		device_unregister(&minor->kdev);
	minor->kdev.parent = NULL;
}