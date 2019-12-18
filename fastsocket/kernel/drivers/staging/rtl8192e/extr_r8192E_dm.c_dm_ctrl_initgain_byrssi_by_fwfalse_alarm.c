#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; scalar_t__ reset_count; scalar_t__ CurrentChannelBW; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int dig_enable_flag; scalar_t__ dig_state; scalar_t__ rssi_low_thresh; scalar_t__ rssi_high_thresh; void* dig_highpwr_state; scalar_t__ dig_algorithm_switch; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 void* DM_STA_DIG_MAX ; 
 scalar_t__ DM_STA_DIG_OFF ; 
 scalar_t__ DM_STA_DIG_ON ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ IEEE80211_LINKED ; 
 int /*<<< orphan*/  UFWP ; 
 int /*<<< orphan*/  bMaskByte1 ; 
 int /*<<< orphan*/  dm_ctrl_initgain_byrssi_highpwr (struct net_device*) ; 
 TYPE_2__ dm_digtable ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int rOFDM0_RxDetector1 ; 
 int rOFDM0_XAAGCCore1 ; 
 int rOFDM0_XATxAFE ; 
 int rOFDM0_XBAGCCore1 ; 
 int rOFDM0_XCAGCCore1 ; 
 int rOFDM0_XDAGCCore1 ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 

__attribute__((used)) static void dm_ctrl_initgain_byrssi_by_fwfalse_alarm(
	struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	static u32 reset_cnt = 0;
	u8 i;

	if (dm_digtable.dig_enable_flag == false)
		return;

	if(dm_digtable.dig_algorithm_switch)
	{
		dm_digtable.dig_state = DM_STA_DIG_MAX;
		// Fw DIG On.
		for(i=0; i<3; i++)
			rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x1);	// Only clear byte 1 and rewrite.
		dm_digtable.dig_algorithm_switch = 0;
	}

	if (priv->ieee80211->state != IEEE80211_LINKED)
		return;

	// For smooth, we can not change DIG state.
	if ((priv->undecorated_smoothed_pwdb > dm_digtable.rssi_low_thresh) &&
		(priv->undecorated_smoothed_pwdb < dm_digtable.rssi_high_thresh))
	{
		return;
	}
	//DbgPrint("Dig by Fw False Alarm\n");
	//if (DM_DigTable.Dig_State == DM_STA_DIG_OFF)
	/*DbgPrint("DIG Check\n\r RSSI=%d LOW=%d HIGH=%d STATE=%d",
	pHalData->UndecoratedSmoothedPWDB, DM_DigTable.RssiLowThresh,
	DM_DigTable.RssiHighThresh, DM_DigTable.Dig_State);*/
	/* 1. When RSSI decrease, We have to judge if it is smaller than a treshold
		  and then execute below step. */
	if ((priv->undecorated_smoothed_pwdb <= dm_digtable.rssi_low_thresh))
	{
		/* 2008/02/05 MH When we execute silent reset, the DIG PHY parameters
		   will be reset to init value. We must prevent the condition. */
		if (dm_digtable.dig_state == DM_STA_DIG_OFF &&
			(priv->reset_count == reset_cnt))
		{
			return;
		}
		else
		{
			reset_cnt = priv->reset_count;
		}

		// If DIG is off, DIG high power state must reset.
		dm_digtable.dig_highpwr_state = DM_STA_DIG_MAX;
		dm_digtable.dig_state = DM_STA_DIG_OFF;

		// 1.1 DIG Off.
		rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);	// Only clear byte 1 and rewrite.

		// 1.2 Set initial gain.
		write_nic_byte(dev, rOFDM0_XAAGCCore1, 0x17);
		write_nic_byte(dev, rOFDM0_XBAGCCore1, 0x17);
		write_nic_byte(dev, rOFDM0_XCAGCCore1, 0x17);
		write_nic_byte(dev, rOFDM0_XDAGCCore1, 0x17);

		// 1.3 Lower PD_TH for OFDM.
		if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
		{
			/* 2008/01/11 MH 40MHZ 90/92 register are not the same. */
			// 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
			#ifdef RTL8190P
			write_nic_byte(dev, rOFDM0_RxDetector1, 0x40);
			#else
				write_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x00);
				#endif
			/*else if (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
				write_nic_byte(pAdapter, rOFDM0_RxDetector1, 0x40);
			*/
			//else if (pAdapter->HardwareType == HARDWARE_TYPE_RTL8192E)


			//else
				//PlatformEFIOWrite1Byte(pAdapter, rOFDM0_RxDetector1, 0x40);
		}
		else
			write_nic_byte(dev, rOFDM0_RxDetector1, 0x42);

		// 1.4 Lower CS ratio for CCK.
		write_nic_byte(dev, 0xa0a, 0x08);

		// 1.5 Higher EDCCA.
		//PlatformEFIOWrite4Byte(pAdapter, rOFDM0_ECCAThreshold, 0x325);
		return;

	}

	/* 2. When RSSI increase, We have to judge if it is larger than a treshold
		  and then execute below step.  */
	if ((priv->undecorated_smoothed_pwdb >= dm_digtable.rssi_high_thresh) )
	{
		u8 reset_flag = 0;

		if (dm_digtable.dig_state == DM_STA_DIG_ON &&
			(priv->reset_count == reset_cnt))
		{
			dm_ctrl_initgain_byrssi_highpwr(dev);
			return;
		}
		else
		{
			if (priv->reset_count != reset_cnt)
				reset_flag = 1;

			reset_cnt = priv->reset_count;
		}

		dm_digtable.dig_state = DM_STA_DIG_ON;
		//DbgPrint("DIG ON\n\r");

		// 2.1 Set initial gain.
		// 2008/02/26 MH SD3-Jerry suggest to prevent dirty environment.
		if (reset_flag == 1)
		{
			write_nic_byte(dev, rOFDM0_XAAGCCore1, 0x2c);
			write_nic_byte(dev, rOFDM0_XBAGCCore1, 0x2c);
			write_nic_byte(dev, rOFDM0_XCAGCCore1, 0x2c);
			write_nic_byte(dev, rOFDM0_XDAGCCore1, 0x2c);
		}
		else
		{
		write_nic_byte(dev, rOFDM0_XAAGCCore1, 0x20);
		write_nic_byte(dev, rOFDM0_XBAGCCore1, 0x20);
		write_nic_byte(dev, rOFDM0_XCAGCCore1, 0x20);
		write_nic_byte(dev, rOFDM0_XDAGCCore1, 0x20);
		}

		// 2.2 Higher PD_TH for OFDM.
		if (priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)
		{
			/* 2008/01/11 MH 40MHZ 90/92 register are not the same. */
			// 2008/02/05 MH SD3-Jerry 92U/92E PD_TH are the same.
			#ifdef RTL8190P
			write_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
			#else
				write_nic_byte(dev, (rOFDM0_XATxAFE+3), 0x20);
				#endif
			/*
			else if (priv->card_8192 == HARDWARE_TYPE_RTL8190P)
				write_nic_byte(dev, rOFDM0_RxDetector1, 0x42);
			*/
			//else if (pAdapter->HardwareType == HARDWARE_TYPE_RTL8192E)

			//else
				//PlatformEFIOWrite1Byte(pAdapter, rOFDM0_RxDetector1, 0x42);
		}
		else
			write_nic_byte(dev, rOFDM0_RxDetector1, 0x44);

		// 2.3 Higher CS ratio for CCK.
		write_nic_byte(dev, 0xa0a, 0xcd);

		// 2.4 Lower EDCCA.
		/* 2008/01/11 MH 90/92 series are the same. */
		//PlatformEFIOWrite4Byte(pAdapter, rOFDM0_ECCAThreshold, 0x346);

		// 2.5 DIG On.
		rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x1);	// Only clear byte 1 and rewrite.

	}

	dm_ctrl_initgain_byrssi_highpwr(dev);

}