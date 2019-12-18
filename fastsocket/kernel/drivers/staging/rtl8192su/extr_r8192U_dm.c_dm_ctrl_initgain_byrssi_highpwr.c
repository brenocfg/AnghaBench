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
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; scalar_t__ reset_count; scalar_t__ CurrentChannelBW; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ rssi_high_power_lowthresh; scalar_t__ rssi_high_power_highthresh; scalar_t__ dig_highpwr_state; scalar_t__ rssi_high_thresh; } ;

/* Variables and functions */
 scalar_t__ DM_STA_DIG_OFF ; 
 scalar_t__ DM_STA_DIG_ON ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  bMaskByte0 ; 
 TYPE_1__ dm_digtable ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ rOFDM0_RxDetector1 ; 
 scalar_t__ rOFDM0_XATxAFE ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 

__attribute__((used)) static void dm_ctrl_initgain_byrssi_highpwr(
	struct net_device * dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	static u32 reset_cnt_highpwr = 0;

	// For smooth, we can not change high power DIG state in the range.
	if ((priv->undecorated_smoothed_pwdb > dm_digtable.rssi_high_power_lowthresh) &&
		(priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_power_highthresh))
	{
		return;
	}

	/* 3. When RSSI >75% or <70%, it is a high power issue. We have to judge if
		  it is larger than a treshold and then execute below step.  */
	// 2008/02/05 MH SD3-Jerry Modify PD_TH for high power issue.
	if (priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_power_highthresh)
	{
		if (dm_digtable.dig_highpwr_state == DM_STA_DIG_ON &&
			(priv->reset_count == reset_cnt_highpwr))
			return;
		else
			dm_digtable.dig_highpwr_state = DM_STA_DIG_ON;

		// 3.1 Higher PD_TH for OFDM for high power state.
		if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
		{
			rtl8192_setBBreg(dev, (rOFDM0_XATxAFE+3), bMaskByte0, 0x10);
			/*else if (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
				write_nic_byte(dev, rOFDM0_RxDetector1, 0x41);
			*/

		}
		else
			write_nic_byte(dev, rOFDM0_RxDetector1, 0x43);
	}
	else
	{
		if (dm_digtable.dig_highpwr_state == DM_STA_DIG_OFF&&
			(priv->reset_count == reset_cnt_highpwr))
			return;
		else
			dm_digtable.dig_highpwr_state = DM_STA_DIG_OFF;

		if (priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_power_lowthresh &&
			 priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_thresh)
		{
			// 3.2 Recover PD_TH for OFDM for normal power region.
			if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
			{
				#ifdef RTL8190P
					write_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
				#else
					write_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x20);
				#endif
				/*else if (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
					write_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
				*/

			}
			else
				write_nic_byte(dev, rOFDM0_RxDetector1, 0x44);
		}
	}

	reset_cnt_highpwr = priv->reset_count;

}