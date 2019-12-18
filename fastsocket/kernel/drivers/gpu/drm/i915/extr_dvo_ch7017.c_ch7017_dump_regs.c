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
typedef  int /*<<< orphan*/  uint8_t ;
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH7017_ACTIVE_INPUT_LINE_OUTPUT ; 
 int /*<<< orphan*/  CH7017_HORIZONTAL_ACTIVE_PIXEL_INPUT ; 
 int /*<<< orphan*/  CH7017_HORIZONTAL_ACTIVE_PIXEL_OUTPUT ; 
 int /*<<< orphan*/  CH7017_LVDS_CONTROL_2 ; 
 int /*<<< orphan*/  CH7017_LVDS_PLL_FEEDBACK_DIV ; 
 int /*<<< orphan*/  CH7017_LVDS_PLL_VCO_CONTROL ; 
 int /*<<< orphan*/  CH7017_LVDS_POWER_DOWN ; 
 int /*<<< orphan*/  CH7017_OUTPUTS_ENABLE ; 
 int /*<<< orphan*/  CH7017_VERTICAL_ACTIVE_LINE_OUTPUT ; 
 int /*<<< orphan*/  DUMP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ch7017_dump_regs(struct intel_dvo_device *dvo)
{
	uint8_t val;

#define DUMP(reg)					\
do {							\
	ch7017_read(dvo, reg, &val);			\
	DRM_DEBUG_KMS(#reg ": %02x\n", val);		\
} while (0)

	DUMP(CH7017_HORIZONTAL_ACTIVE_PIXEL_INPUT);
	DUMP(CH7017_HORIZONTAL_ACTIVE_PIXEL_OUTPUT);
	DUMP(CH7017_VERTICAL_ACTIVE_LINE_OUTPUT);
	DUMP(CH7017_ACTIVE_INPUT_LINE_OUTPUT);
	DUMP(CH7017_LVDS_PLL_VCO_CONTROL);
	DUMP(CH7017_LVDS_PLL_FEEDBACK_DIV);
	DUMP(CH7017_LVDS_CONTROL_2);
	DUMP(CH7017_OUTPUTS_ENABLE);
	DUMP(CH7017_LVDS_POWER_DOWN);
}