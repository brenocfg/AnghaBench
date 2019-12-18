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
struct intel_sdvo_dtd {int dummy; } ;
struct intel_sdvo {int /*<<< orphan*/  attached_output; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_sdvo_get_dtd_from_mode (struct intel_sdvo_dtd*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  intel_sdvo_set_output_timing (struct intel_sdvo*,struct intel_sdvo_dtd*) ; 
 int /*<<< orphan*/  intel_sdvo_set_target_output (struct intel_sdvo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_sdvo_set_output_timings_from_mode(struct intel_sdvo *intel_sdvo,
					const struct drm_display_mode *mode)
{
	struct intel_sdvo_dtd output_dtd;

	if (!intel_sdvo_set_target_output(intel_sdvo,
					  intel_sdvo->attached_output))
		return false;

	intel_sdvo_get_dtd_from_mode(&output_dtd, mode);
	if (!intel_sdvo_set_output_timing(intel_sdvo, &output_dtd))
		return false;

	return true;
}