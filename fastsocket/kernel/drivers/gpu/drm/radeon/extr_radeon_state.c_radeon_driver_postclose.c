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
struct drm_radeon_driver_file_fields {int dummy; } ;
struct drm_file {struct drm_radeon_driver_file_fields* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct drm_radeon_driver_file_fields*) ; 

void radeon_driver_postclose(struct drm_device *dev, struct drm_file *file_priv)
{
	struct drm_radeon_driver_file_fields *radeon_priv =
	    file_priv->driver_priv;

	kfree(radeon_priv);
}