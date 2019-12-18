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
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_fb_output_poll_changed (struct radeon_device*) ; 

__attribute__((used)) static void radeon_output_poll_changed(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	radeon_fb_output_poll_changed(rdev);
}