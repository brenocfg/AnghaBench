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
struct rt2x00_dev {int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_POWER_LIMIT ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt2800_get_txpower_reg_delta(struct rt2x00_dev *rt2x00dev,
					int power_level, int max_power)
{
	int delta;

	if (test_bit(CAPABILITY_POWER_LIMIT, &rt2x00dev->cap_flags))
		return 0;

	/*
	 * XXX: We don't know the maximum transmit power of our hardware since
	 * the EEPROM doesn't expose it. We only know that we are calibrated
	 * to 100% tx power.
	 *
	 * Hence, we assume the regulatory limit that cfg80211 calulated for
	 * the current channel is our maximum and if we are requested to lower
	 * the value we just reduce our tx power accordingly.
	 */
	delta = power_level - max_power;
	return min(delta, 0);
}