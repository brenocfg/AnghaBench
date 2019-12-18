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
struct drm_radeon_driver_file_fields {scalar_t__ radeon_fb_delta; } ;
struct drm_file {struct drm_radeon_driver_file_fields* driver_priv; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {scalar_t__ fb_location; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_radeon_driver_file_fields* kmalloc (int,int /*<<< orphan*/ ) ; 

int radeon_driver_open(struct drm_device *dev, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_driver_file_fields *radeon_priv;

	DRM_DEBUG("\n");
	radeon_priv = kmalloc(sizeof(*radeon_priv), GFP_KERNEL);

	if (!radeon_priv)
		return -ENOMEM;

	file_priv->driver_priv = radeon_priv;

	if (dev_priv)
		radeon_priv->radeon_fb_delta = dev_priv->fb_location;
	else
		radeon_priv->radeon_fb_delta = 0;
	return 0;
}