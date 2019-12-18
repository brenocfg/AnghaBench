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
struct drm_display_mode {int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_object_put (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_display_mode*) ; 

void drm_mode_destroy(struct drm_device *dev, struct drm_display_mode *mode)
{
	if (!mode)
		return;

	drm_mode_object_put(dev, &mode->base);

	kfree(mode);
}