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
struct intel_sdvo {int /*<<< orphan*/  hotplug_active; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDVO_CMD_SET_ACTIVE_HOT_PLUG ; 
 int /*<<< orphan*/  intel_sdvo_write_cmd (struct intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct intel_sdvo* to_intel_sdvo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_sdvo_enable_hotplug(struct intel_encoder *encoder)
{
	struct intel_sdvo *intel_sdvo = to_intel_sdvo(&encoder->base);

	intel_sdvo_write_cmd(intel_sdvo, SDVO_CMD_SET_ACTIVE_HOT_PLUG,
			&intel_sdvo->hotplug_active, 2);
}