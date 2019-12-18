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
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_dp_encoder_destroy (struct drm_encoder*) ; 

__attribute__((used)) static void intel_ddi_destroy(struct drm_encoder *encoder)
{
	/* HDMI has nothing special to destroy, so we can go with this. */
	intel_dp_encoder_destroy(encoder);
}