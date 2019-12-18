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
typedef  int /*<<< orphan*/  targets ;
struct intel_sdvo_set_target_input_args {int /*<<< orphan*/  member_0; } ;
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDVO_CMD_SET_TARGET_INPUT ; 
 int intel_sdvo_set_value (struct intel_sdvo*,int /*<<< orphan*/ ,struct intel_sdvo_set_target_input_args*,int) ; 

__attribute__((used)) static bool intel_sdvo_set_target_input(struct intel_sdvo *intel_sdvo)
{
	struct intel_sdvo_set_target_input_args targets = {0};
	return intel_sdvo_set_value(intel_sdvo,
				    SDVO_CMD_SET_TARGET_INPUT,
				    &targets, sizeof(targets));
}