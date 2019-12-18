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
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int intel_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool haswell_crtc_driving_pch(struct drm_crtc *crtc)
{
	return intel_pipe_has_type(crtc, INTEL_OUTPUT_ANALOG);
}