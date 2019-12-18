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
struct r8180_priv {int* chtxpwr; int* chtxpwr_ofdm; scalar_t__ card_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8225_ANAPARAM2_ON ; 
 int /*<<< orphan*/  TX_GAIN_CCK ; 
 int /*<<< orphan*/  TX_GAIN_OFDM ; 
 scalar_t__ USB ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8185_set_anaparam2 (struct net_device*,int /*<<< orphan*/ ) ; 
 int* rtl8225_tx_gain_cck_ofdm ; 
 int* rtl8225_tx_power_cck ; 
 int* rtl8225_tx_power_cck_ch14 ; 
 int* rtl8225_tx_power_ofdm ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_phy_cck (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 

__attribute__((used)) static void rtl8225_SetTXPowerLevel(struct net_device *dev, short ch)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	int GainIdx;
	int GainSetting;
	int i;
	u8 power;
	const u8 *cck_power_table;
	u8 max_cck_power_level;
	u8 max_ofdm_power_level;
	u8 min_ofdm_power_level;
	u8 cck_power_level = 0xff & priv->chtxpwr[ch];
	u8 ofdm_power_level = 0xff & priv->chtxpwr_ofdm[ch];

	if (priv->card_type == USB) {
		max_cck_power_level = 11;
		max_ofdm_power_level = 25;
		min_ofdm_power_level = 10;
	} else {
		max_cck_power_level = 35;
		max_ofdm_power_level = 35;
		min_ofdm_power_level = 0;
	}

	if (cck_power_level > max_cck_power_level)
		cck_power_level = max_cck_power_level;

	GainIdx = cck_power_level % 6;
	GainSetting = cck_power_level / 6;

	if (ch == 14)
		cck_power_table = rtl8225_tx_power_cck_ch14;
	else
		cck_power_table = rtl8225_tx_power_cck;

	write_nic_byte(dev, TX_GAIN_CCK,
		       rtl8225_tx_gain_cck_ofdm[GainSetting] >> 1);

	for (i = 0; i < 8; i++) {
		power = cck_power_table[GainIdx * 8 + i];
		write_phy_cck(dev, 0x44 + i, power);
	}

	/* FIXME Is this delay really needeed ? */
	force_pci_posting(dev);
	mdelay(1);

	if (ofdm_power_level > (max_ofdm_power_level - min_ofdm_power_level))
		ofdm_power_level = max_ofdm_power_level;
	else
		ofdm_power_level += min_ofdm_power_level;

	if (ofdm_power_level > 35)
		ofdm_power_level = 35;

	GainIdx = ofdm_power_level % 6;
	GainSetting = ofdm_power_level / 6;

	rtl8185_set_anaparam2(dev, RTL8225_ANAPARAM2_ON);

	write_phy_ofdm(dev, 2, 0x42);
	write_phy_ofdm(dev, 6, 0x00);
	write_phy_ofdm(dev, 8, 0x00);

	write_nic_byte(dev, TX_GAIN_OFDM,
		       rtl8225_tx_gain_cck_ofdm[GainSetting] >> 1);

	power = rtl8225_tx_power_ofdm[GainIdx];

	write_phy_ofdm(dev, 5, power);
	write_phy_ofdm(dev, 7, power);

	force_pci_posting(dev);
	mdelay(1);
}