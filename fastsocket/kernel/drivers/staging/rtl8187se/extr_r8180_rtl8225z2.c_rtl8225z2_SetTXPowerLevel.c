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
typedef  char u8 ;
struct r8180_priv {int* chtxpwr; int* chtxpwr_ofdm; scalar_t__ up; int /*<<< orphan*/  ieee80211; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_TXAGC ; 
 char DOT11D_GetMaxTxPwrInDbm (int /*<<< orphan*/ ,short) ; 
 char DbmToTxPwrIdx (struct r8180_priv*,int /*<<< orphan*/ ,char) ; 
 scalar_t__ IS_DOT11D_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DOT11D_STATE_DONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFDM_TXAGC ; 
 int /*<<< orphan*/  WIRELESS_MODE_B ; 
 int /*<<< orphan*/  WIRELESS_MODE_G ; 
 int /*<<< orphan*/ * ZEBRA2_CCK_OFDM_GAIN_SETTING ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 

void rtl8225z2_SetTXPowerLevel(struct net_device *dev, short ch)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u8 max_cck_power_level;
	u8 max_ofdm_power_level;
	u8 min_ofdm_power_level;
	char cck_power_level = (char)(0xff & priv->chtxpwr[ch]);
	char ofdm_power_level = (char)(0xff & priv->chtxpwr_ofdm[ch]);

	if (IS_DOT11D_ENABLE(priv->ieee80211) &&
	    IS_DOT11D_STATE_DONE(priv->ieee80211)) {
		u8 MaxTxPwrInDbm = DOT11D_GetMaxTxPwrInDbm(priv->ieee80211, ch);
		u8 CckMaxPwrIdx = DbmToTxPwrIdx(priv, WIRELESS_MODE_B, MaxTxPwrInDbm);
		u8 OfdmMaxPwrIdx = DbmToTxPwrIdx(priv, WIRELESS_MODE_G, MaxTxPwrInDbm);

		if (cck_power_level > CckMaxPwrIdx)
			cck_power_level = CckMaxPwrIdx;
		if (ofdm_power_level > OfdmMaxPwrIdx)
			ofdm_power_level = OfdmMaxPwrIdx;
	}

	max_cck_power_level = 15;
	max_ofdm_power_level = 25;
	min_ofdm_power_level = 10;

	if (cck_power_level > 35)
		cck_power_level = 35;

	write_nic_byte(dev, CCK_TXAGC,
		       (ZEBRA2_CCK_OFDM_GAIN_SETTING[(u8)cck_power_level]));
	force_pci_posting(dev);
	mdelay(1);

	if (ofdm_power_level > 35)
		ofdm_power_level = 35;

	if (priv->up == 0) {
		write_phy_ofdm(dev, 2, 0x42);
		write_phy_ofdm(dev, 5, 0x00);
		write_phy_ofdm(dev, 6, 0x40);
		write_phy_ofdm(dev, 7, 0x00);
		write_phy_ofdm(dev, 8, 0x40);
	}

	write_nic_byte(dev, OFDM_TXAGC,
		       ZEBRA2_CCK_OFDM_GAIN_SETTING[(u8)ofdm_power_level]);

	if (ofdm_power_level <= 11) {
		write_phy_ofdm(dev, 0x07, 0x5c);
		write_phy_ofdm(dev, 0x09, 0x5c);
        }

	if (ofdm_power_level <= 17) {
		write_phy_ofdm(dev, 0x07, 0x54);
		write_phy_ofdm(dev, 0x09, 0x54);
	} else {
		write_phy_ofdm(dev, 0x07, 0x50);
		write_phy_ofdm(dev, 0x09, 0x50);
	}

	force_pci_posting(dev);
	mdelay(1);
}