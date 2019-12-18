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
typedef  int uint16_t ;
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VR01 ; 
 int VR01_DVO_ENABLE ; 
 int VR01_LCD_ENABLE ; 
 int /*<<< orphan*/  VR30 ; 
 int VR30_PANEL_ON ; 
 int /*<<< orphan*/  VR80 ; 
 int /*<<< orphan*/  ivch_read (struct intel_dvo_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ivch_write (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ivch_dpms(struct intel_dvo_device *dvo, bool enable)
{
	int i;
	uint16_t vr01, vr30, backlight;

	/* Set the new power state of the panel. */
	if (!ivch_read(dvo, VR01, &vr01))
		return;

	if (enable)
		backlight = 1;
	else
		backlight = 0;
	ivch_write(dvo, VR80, backlight);

	if (enable)
		vr01 |= VR01_LCD_ENABLE | VR01_DVO_ENABLE;
	else
		vr01 &= ~(VR01_LCD_ENABLE | VR01_DVO_ENABLE);

	ivch_write(dvo, VR01, vr01);

	/* Wait for the panel to make its state transition */
	for (i = 0; i < 100; i++) {
		if (!ivch_read(dvo, VR30, &vr30))
			break;

		if (((vr30 & VR30_PANEL_ON) != 0) == enable)
			break;
		udelay(1000);
	}
	/* wait some more; vch may fail to resync sometimes without this */
	udelay(16 * 1000);
}