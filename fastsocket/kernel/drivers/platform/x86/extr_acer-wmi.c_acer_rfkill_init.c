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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACER_CAP_BLUETOOTH ; 
 int /*<<< orphan*/  ACER_CAP_WIRELESS ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  acer_rfkill_register (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acer_rfkill_work ; 
 int /*<<< orphan*/  bluetooth_rfkill ; 
 scalar_t__ has_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_rfkill ; 

__attribute__((used)) static int acer_rfkill_init(struct device *dev)
{
	wireless_rfkill = acer_rfkill_register(dev, RFKILL_TYPE_WLAN,
		"acer-wireless", ACER_CAP_WIRELESS);
	if (IS_ERR(wireless_rfkill))
		return PTR_ERR(wireless_rfkill);

	if (has_cap(ACER_CAP_BLUETOOTH)) {
		bluetooth_rfkill = acer_rfkill_register(dev,
			RFKILL_TYPE_BLUETOOTH, "acer-bluetooth",
			ACER_CAP_BLUETOOTH);
		if (IS_ERR(bluetooth_rfkill)) {
			rfkill_unregister(wireless_rfkill);
			rfkill_destroy(wireless_rfkill);
			return PTR_ERR(bluetooth_rfkill);
		}
	}

	schedule_delayed_work(&acer_rfkill_work, round_jiffies_relative(HZ));

	return 0;
}