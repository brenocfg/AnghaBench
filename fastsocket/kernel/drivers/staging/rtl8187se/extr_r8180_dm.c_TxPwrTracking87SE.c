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
struct r8180_priv {int ThermalMeter; char* chtxpwr; char* chtxpwr_ofdm; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  EN_LPF_CAL ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8225z2_SetTXPowerLevel (struct net_device*,int /*<<< orphan*/ ) ; 

void
TxPwrTracking87SE(
	struct net_device *dev
)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	u8	tmpu1Byte, CurrentThermal, Idx;
	char	CckTxPwrIdx, OfdmTxPwrIdx;
	//u32	u4bRfReg;

	tmpu1Byte = read_nic_byte(dev, EN_LPF_CAL);
	CurrentThermal = (tmpu1Byte & 0xf0)>>4; //[ 7:4]: thermal meter indication.
	CurrentThermal = (CurrentThermal>0x0c)? 0x0c:CurrentThermal;//lzm add 080826

	//printk("TxPwrTracking87SE(): CurrentThermal(%d)\n", CurrentThermal);

	if( CurrentThermal != priv->ThermalMeter)
	{
//		printk("TxPwrTracking87SE(): Thermal meter changed!!!\n");

		// Update Tx Power level on each channel.
		for(Idx = 1; Idx<15; Idx++)
		{
			CckTxPwrIdx = priv->chtxpwr[Idx];
			OfdmTxPwrIdx = priv->chtxpwr_ofdm[Idx];

			if( CurrentThermal > priv->ThermalMeter )
			{ // higher thermal meter.
				CckTxPwrIdx += (CurrentThermal - priv->ThermalMeter)*2;
				OfdmTxPwrIdx += (CurrentThermal - priv->ThermalMeter)*2;

				if(CckTxPwrIdx >35)
					CckTxPwrIdx = 35; // Force TxPower to maximal index.
				if(OfdmTxPwrIdx >35)
					OfdmTxPwrIdx = 35;
			}
			else
			{ // lower thermal meter.
				CckTxPwrIdx -= (priv->ThermalMeter - CurrentThermal)*2;
				OfdmTxPwrIdx -= (priv->ThermalMeter - CurrentThermal)*2;

				if(CckTxPwrIdx <0)
					CckTxPwrIdx = 0;
				if(OfdmTxPwrIdx <0)
					OfdmTxPwrIdx = 0;
			}

			// Update TxPower level on CCK and OFDM resp.
			priv->chtxpwr[Idx] = CckTxPwrIdx;
			priv->chtxpwr_ofdm[Idx] = OfdmTxPwrIdx;
		}

		// Update TxPower level immediately.
		rtl8225z2_SetTXPowerLevel(dev, priv->ieee80211->current_network.channel);
	}
	priv->ThermalMeter = CurrentThermal;
}