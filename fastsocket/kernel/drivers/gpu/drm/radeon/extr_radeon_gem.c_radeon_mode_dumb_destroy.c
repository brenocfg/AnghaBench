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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_gem_handle_delete (struct drm_file*,int /*<<< orphan*/ ) ; 

int radeon_mode_dumb_destroy(struct drm_file *file_priv,
			     struct drm_device *dev,
			     uint32_t handle)
{
	return drm_gem_handle_delete(file_priv, handle);
}