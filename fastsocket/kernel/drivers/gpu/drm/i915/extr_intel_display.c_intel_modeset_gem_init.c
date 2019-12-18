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
 int /*<<< orphan*/  intel_modeset_init_hw (struct drm_device*) ; 
 int /*<<< orphan*/  intel_modeset_setup_hw_state (struct drm_device*,int) ; 
 int /*<<< orphan*/  intel_setup_overlay (struct drm_device*) ; 

void intel_modeset_gem_init(struct drm_device *dev)
{
	intel_modeset_init_hw(dev);

	intel_setup_overlay(dev);

	intel_modeset_setup_hw_state(dev, false);
}