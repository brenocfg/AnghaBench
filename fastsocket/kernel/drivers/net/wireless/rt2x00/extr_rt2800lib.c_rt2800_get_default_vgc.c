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
typedef  int u8 ;
struct rt2x00_dev {scalar_t__ curr_band; int lna_gain; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CHANNEL_HT40 ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3071 ; 
 int /*<<< orphan*/  RT3090 ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  RT3390 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  RT5390 ; 
 int /*<<< orphan*/  RT5392 ; 
 int /*<<< orphan*/  RT5592 ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 rt2800_get_default_vgc(struct rt2x00_dev *rt2x00dev)
{
	u8 vgc;

	if (rt2x00dev->curr_band == IEEE80211_BAND_2GHZ) {
		if (rt2x00_rt(rt2x00dev, RT3070) ||
		    rt2x00_rt(rt2x00dev, RT3071) ||
		    rt2x00_rt(rt2x00dev, RT3090) ||
		    rt2x00_rt(rt2x00dev, RT3290) ||
		    rt2x00_rt(rt2x00dev, RT3390) ||
		    rt2x00_rt(rt2x00dev, RT3572) ||
		    rt2x00_rt(rt2x00dev, RT5390) ||
		    rt2x00_rt(rt2x00dev, RT5392) ||
		    rt2x00_rt(rt2x00dev, RT5592))
			vgc = 0x1c + (2 * rt2x00dev->lna_gain);
		else
			vgc = 0x2e + rt2x00dev->lna_gain;
	} else { /* 5GHZ band */
		if (rt2x00_rt(rt2x00dev, RT3572))
			vgc = 0x22 + (rt2x00dev->lna_gain * 5) / 3;
		else if (rt2x00_rt(rt2x00dev, RT5592))
			vgc = 0x24 + (2 * rt2x00dev->lna_gain);
		else {
			if (!test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags))
				vgc = 0x32 + (rt2x00dev->lna_gain * 5) / 3;
			else
				vgc = 0x3a + (rt2x00dev->lna_gain * 5) / 3;
		}
	}

	return vgc;
}