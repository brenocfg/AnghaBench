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
struct intel_hdmi {int /*<<< orphan*/  (* write_infoframe ) (struct drm_encoder*,struct dip_infoframe*) ;} ;
struct drm_encoder {int dummy; } ;
struct dip_infoframe {int dummy; } ;

/* Variables and functions */
 struct intel_hdmi* enc_to_intel_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_dip_infoframe_csum (struct dip_infoframe*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,struct dip_infoframe*) ; 

__attribute__((used)) static void intel_set_infoframe(struct drm_encoder *encoder,
				struct dip_infoframe *frame)
{
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);

	intel_dip_infoframe_csum(frame);
	intel_hdmi->write_infoframe(encoder, frame);
}