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
typedef  int u16 ;
struct lpphy_tx_gains {int dac; int gm; int pga; int pad; } ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_AFE_DAC_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lpphy_tx_gains lpphy_get_tx_gains(struct b43_wldev *dev)
{
	struct lpphy_tx_gains gains;
	u16 tmp;

	gains.dac = (b43_phy_read(dev, B43_LPPHY_AFE_DAC_CTL) & 0x380) >> 7;
	if (dev->phy.rev < 2) {
		tmp = b43_phy_read(dev,
				   B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL) & 0x7FF;
		gains.gm = tmp & 0x0007;
		gains.pga = (tmp & 0x0078) >> 3;
		gains.pad = (tmp & 0x780) >> 7;
	} else {
		tmp = b43_phy_read(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL);
		gains.pad = b43_phy_read(dev, B43_PHY_OFDM(0xFB)) & 0xFF;
		gains.gm = tmp & 0xFF;
		gains.pga = (tmp >> 8) & 0xFF;
	}

	return gains;
}