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
struct intel_sdvo_caps {int /*<<< orphan*/  output_flags; int /*<<< orphan*/  stall_support; int /*<<< orphan*/  down_scaling; int /*<<< orphan*/  up_scaling; int /*<<< orphan*/  sharp_scaling; int /*<<< orphan*/  smooth_scaling; int /*<<< orphan*/  sdvo_inputs_mask; int /*<<< orphan*/  sdvo_version_minor; int /*<<< orphan*/  sdvo_version_major; int /*<<< orphan*/  device_rev_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDVO_CMD_GET_DEVICE_CAPS ; 
 int /*<<< orphan*/  intel_sdvo_get_value (struct intel_sdvo*,int /*<<< orphan*/ ,struct intel_sdvo_caps*,int) ; 

__attribute__((used)) static bool intel_sdvo_get_capabilities(struct intel_sdvo *intel_sdvo, struct intel_sdvo_caps *caps)
{
	BUILD_BUG_ON(sizeof(*caps) != 8);
	if (!intel_sdvo_get_value(intel_sdvo,
				  SDVO_CMD_GET_DEVICE_CAPS,
				  caps, sizeof(*caps)))
		return false;

	DRM_DEBUG_KMS("SDVO capabilities:\n"
		      "  vendor_id: %d\n"
		      "  device_id: %d\n"
		      "  device_rev_id: %d\n"
		      "  sdvo_version_major: %d\n"
		      "  sdvo_version_minor: %d\n"
		      "  sdvo_inputs_mask: %d\n"
		      "  smooth_scaling: %d\n"
		      "  sharp_scaling: %d\n"
		      "  up_scaling: %d\n"
		      "  down_scaling: %d\n"
		      "  stall_support: %d\n"
		      "  output_flags: %d\n",
		      caps->vendor_id,
		      caps->device_id,
		      caps->device_rev_id,
		      caps->sdvo_version_major,
		      caps->sdvo_version_minor,
		      caps->sdvo_inputs_mask,
		      caps->smooth_scaling,
		      caps->sharp_scaling,
		      caps->up_scaling,
		      caps->down_scaling,
		      caps->stall_support,
		      caps->output_flags);

	return true;
}