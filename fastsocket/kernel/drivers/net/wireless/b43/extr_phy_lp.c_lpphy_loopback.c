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
struct lpphy_iq_est {int i_pwr; int q_pwr; } ;
struct b43_wldev {int dummy; } ;
typedef  int /*<<< orphan*/  iq_est ;

/* Variables and functions */
 int /*<<< orphan*/  B2062_N_TX_CTL_A ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_VAL_0 ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_run_ddfs (struct b43_wldev*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_rx_iq_est (struct b43_wldev*,int,int,struct lpphy_iq_est*) ; 
 int /*<<< orphan*/  lpphy_set_rx_gain_by_index (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_trsw_over (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  lpphy_stop_ddfs (struct b43_wldev*) ; 
 int /*<<< orphan*/  memset (struct lpphy_iq_est*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lpphy_loopback(struct b43_wldev *dev)
{
	struct lpphy_iq_est iq_est;
	int i, index = -1;
	u32 tmp;

	memset(&iq_est, 0, sizeof(iq_est));

	lpphy_set_trsw_over(dev, true, true);
	b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVR, 1);
	b43_phy_mask(dev, B43_LPPHY_AFE_CTL_OVRVAL, 0xFFFE);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x800);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x800);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x8);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x8);
	b43_radio_write(dev, B2062_N_TX_CTL_A, 0x80);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x80);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x80);
	for (i = 0; i < 32; i++) {
		lpphy_set_rx_gain_by_index(dev, i);
		lpphy_run_ddfs(dev, 1, 1, 5, 5, 0);
		if (!(lpphy_rx_iq_est(dev, 1000, 32, &iq_est)))
			continue;
		tmp = (iq_est.i_pwr + iq_est.q_pwr) / 1000;
		if ((tmp > 4000) && (tmp < 10000)) {
			index = i;
			break;
		}
	}
	lpphy_stop_ddfs(dev);
	return index;
}