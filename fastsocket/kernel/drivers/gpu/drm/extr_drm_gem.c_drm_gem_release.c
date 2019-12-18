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
struct drm_file {int /*<<< orphan*/  object_idr; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_release_handle ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_file*) ; 
 int /*<<< orphan*/  idr_remove_all (int /*<<< orphan*/ *) ; 

void
drm_gem_release(struct drm_device *dev, struct drm_file *file_private)
{
	idr_for_each(&file_private->object_idr,
		     &drm_gem_object_release_handle, file_private);

	idr_remove_all(&file_private->object_idr);
	idr_destroy(&file_private->object_idr);
}