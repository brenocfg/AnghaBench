#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int radio_ver; struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_lp {unsigned int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_CHANNEL ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  channel2freq_lp (unsigned int) ; 
 int /*<<< orphan*/  lpphy_adjust_gain_table (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int lpphy_b2062_tune (struct b43_wldev*,unsigned int) ; 
 int lpphy_b2063_tune (struct b43_wldev*,unsigned int) ; 
 int /*<<< orphan*/  lpphy_set_analog_filter (struct b43_wldev*,unsigned int) ; 

__attribute__((used)) static int b43_lpphy_op_switch_channel(struct b43_wldev *dev,
				       unsigned int new_channel)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	int err;

	if (dev->phy.radio_ver == 0x2063) {
		err = lpphy_b2063_tune(dev, new_channel);
		if (err)
			return err;
	} else {
		err = lpphy_b2062_tune(dev, new_channel);
		if (err)
			return err;
		lpphy_set_analog_filter(dev, new_channel);
		lpphy_adjust_gain_table(dev, channel2freq_lp(new_channel));
	}

	lpphy->channel = new_channel;
	b43_write16(dev, B43_MMIO_CHANNEL, new_channel);

	return 0;
}