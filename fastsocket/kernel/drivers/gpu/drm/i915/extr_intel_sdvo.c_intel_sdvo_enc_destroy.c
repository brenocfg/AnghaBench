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
struct intel_sdvo {int /*<<< orphan*/  ddc; int /*<<< orphan*/ * sdvo_lvds_fixed_mode; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_encoder_destroy (struct drm_encoder*) ; 
 struct intel_sdvo* to_intel_sdvo (struct drm_encoder*) ; 

__attribute__((used)) static void intel_sdvo_enc_destroy(struct drm_encoder *encoder)
{
	struct intel_sdvo *intel_sdvo = to_intel_sdvo(encoder);

	if (intel_sdvo->sdvo_lvds_fixed_mode != NULL)
		drm_mode_destroy(encoder->dev,
				 intel_sdvo->sdvo_lvds_fixed_mode);

	i2c_del_adapter(&intel_sdvo->ddc);
	intel_encoder_destroy(encoder);
}