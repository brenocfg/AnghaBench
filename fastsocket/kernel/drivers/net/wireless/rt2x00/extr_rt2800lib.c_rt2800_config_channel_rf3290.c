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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {int dummy; } ;
struct rf_channel {scalar_t__ rf2; int channel; int /*<<< orphan*/  rf3; int /*<<< orphan*/  rf1; } ;
struct ieee80211_conf {int dummy; } ;
struct channel_info {scalar_t__ default_power1; } ;

/* Variables and functions */
 scalar_t__ POWER_BOUND ; 
 int /*<<< orphan*/  RFCSR11_R ; 
 int /*<<< orphan*/  RFCSR49_TX ; 
 int /*<<< orphan*/  rt2800_adjust_freq_offset (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rt2800_config_channel_rf3290(struct rt2x00_dev *rt2x00dev,
					 struct ieee80211_conf *conf,
					 struct rf_channel *rf,
					 struct channel_info *info)
{
	u8 rfcsr;

	rt2800_rfcsr_write(rt2x00dev, 8, rf->rf1);
	rt2800_rfcsr_write(rt2x00dev, 9, rf->rf3);
	rt2800_rfcsr_read(rt2x00dev, 11, &rfcsr);
	rt2x00_set_field8(&rfcsr, RFCSR11_R, rf->rf2);
	rt2800_rfcsr_write(rt2x00dev, 11, rfcsr);

	rt2800_rfcsr_read(rt2x00dev, 49, &rfcsr);
	if (info->default_power1 > POWER_BOUND)
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, POWER_BOUND);
	else
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, info->default_power1);
	rt2800_rfcsr_write(rt2x00dev, 49, rfcsr);

	rt2800_adjust_freq_offset(rt2x00dev);

	if (rf->channel <= 14) {
		if (rf->channel == 6)
			rt2800_bbp_write(rt2x00dev, 68, 0x0c);
		else
			rt2800_bbp_write(rt2x00dev, 68, 0x0b);

		if (rf->channel >= 1 && rf->channel <= 6)
			rt2800_bbp_write(rt2x00dev, 59, 0x0f);
		else if (rf->channel >= 7 && rf->channel <= 11)
			rt2800_bbp_write(rt2x00dev, 59, 0x0e);
		else if (rf->channel >= 12 && rf->channel <= 14)
			rt2800_bbp_write(rt2x00dev, 59, 0x0d);
	}
}