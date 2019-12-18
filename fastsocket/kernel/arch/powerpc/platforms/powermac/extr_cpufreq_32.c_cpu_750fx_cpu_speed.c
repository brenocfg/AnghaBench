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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_WRITE_GPIO ; 
 int /*<<< orphan*/  SPRN_HID2 ; 
 scalar_t__ has_cpu_l2lve ; 
 int /*<<< orphan*/  local_delay (int) ; 
 int /*<<< orphan*/  low_choose_750fx_pll (int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  voltage_gpio ; 

__attribute__((used)) static int cpu_750fx_cpu_speed(int low_speed)
{
	u32 hid2;

	if (low_speed == 0) {
		/* ramping up, set voltage first */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, voltage_gpio, 0x05);
		/* Make sure we sleep for at least 1ms */
		local_delay(10);

		/* tweak L2 for high voltage */
		if (has_cpu_l2lve) {
			hid2 = mfspr(SPRN_HID2);
			hid2 &= ~0x2000;
			mtspr(SPRN_HID2, hid2);
		}
	}
#ifdef CONFIG_6xx
	low_choose_750fx_pll(low_speed);
#endif
	if (low_speed == 1) {
		/* tweak L2 for low voltage */
		if (has_cpu_l2lve) {
			hid2 = mfspr(SPRN_HID2);
			hid2 |= 0x2000;
			mtspr(SPRN_HID2, hid2);
		}

		/* ramping down, set voltage last */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, voltage_gpio, 0x04);
		local_delay(10);
	}

	return 0;
}