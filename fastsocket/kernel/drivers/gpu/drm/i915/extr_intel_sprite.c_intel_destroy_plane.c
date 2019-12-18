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
struct intel_plane {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 int /*<<< orphan*/  intel_disable_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  kfree (struct intel_plane*) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static void intel_destroy_plane(struct drm_plane *plane)
{
	struct intel_plane *intel_plane = to_intel_plane(plane);
	intel_disable_plane(plane);
	drm_plane_cleanup(plane);
	kfree(intel_plane);
}