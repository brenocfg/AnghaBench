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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8187_priv {TYPE_1__* map; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rtl8187_priv* priv; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  TX_ANTENNA; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int* rtl8225_agc ; 
 int rtl8225_read (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8225_write (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8225_write_phy_cck (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8225_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 
 int* rtl8225z2_gain_bg ; 
 int /*<<< orphan*/  rtl8225z2_rf_set_tx_power (struct ieee80211_hw*,int) ; 
 int* rtl8225z2_rxgain ; 
 int /*<<< orphan*/  wiphy_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void rtl8225z2_rf_init(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	int i;

	rtl8225_write(dev, 0x0, 0x2BF);
	rtl8225_write(dev, 0x1, 0xEE0);
	rtl8225_write(dev, 0x2, 0x44D);
	rtl8225_write(dev, 0x3, 0x441);
	rtl8225_write(dev, 0x4, 0x8C3);
	rtl8225_write(dev, 0x5, 0xC72);
	rtl8225_write(dev, 0x6, 0x0E6);
	rtl8225_write(dev, 0x7, 0x82A);
	rtl8225_write(dev, 0x8, 0x03F);
	rtl8225_write(dev, 0x9, 0x335);
	rtl8225_write(dev, 0xa, 0x9D4);
	rtl8225_write(dev, 0xb, 0x7BB);
	rtl8225_write(dev, 0xc, 0x850);
	rtl8225_write(dev, 0xd, 0xCDF);
	rtl8225_write(dev, 0xe, 0x02B);
	rtl8225_write(dev, 0xf, 0x114);
	msleep(100);

	rtl8225_write(dev, 0x0, 0x1B7);

	for (i = 0; i < ARRAY_SIZE(rtl8225z2_rxgain); i++) {
		rtl8225_write(dev, 0x1, i + 1);
		rtl8225_write(dev, 0x2, rtl8225z2_rxgain[i]);
	}

	rtl8225_write(dev, 0x3, 0x080);
	rtl8225_write(dev, 0x5, 0x004);
	rtl8225_write(dev, 0x0, 0x0B7);
	rtl8225_write(dev, 0x2, 0xc4D);

	msleep(200);
	rtl8225_write(dev, 0x2, 0x44D);
	msleep(100);

	if (!(rtl8225_read(dev, 6) & (1 << 7))) {
		rtl8225_write(dev, 0x02, 0x0C4D);
		msleep(200);
		rtl8225_write(dev, 0x02, 0x044D);
		msleep(100);
		if (!(rtl8225_read(dev, 6) & (1 << 7)))
			wiphy_warn(dev->wiphy, "RF Calibration Failed! %x\n",
				   rtl8225_read(dev, 6));
	}

	msleep(200);

	rtl8225_write(dev, 0x0, 0x2BF);

	for (i = 0; i < ARRAY_SIZE(rtl8225_agc); i++) {
		rtl8225_write_phy_ofdm(dev, 0xB, rtl8225_agc[i]);
		rtl8225_write_phy_ofdm(dev, 0xA, 0x80 + i);
	}

	msleep(1);

	rtl8225_write_phy_ofdm(dev, 0x00, 0x01);
	rtl8225_write_phy_ofdm(dev, 0x01, 0x02);
	rtl8225_write_phy_ofdm(dev, 0x02, 0x42);
	rtl8225_write_phy_ofdm(dev, 0x03, 0x00);
	rtl8225_write_phy_ofdm(dev, 0x04, 0x00);
	rtl8225_write_phy_ofdm(dev, 0x05, 0x00);
	rtl8225_write_phy_ofdm(dev, 0x06, 0x40);
	rtl8225_write_phy_ofdm(dev, 0x07, 0x00);
	rtl8225_write_phy_ofdm(dev, 0x08, 0x40);
	rtl8225_write_phy_ofdm(dev, 0x09, 0xfe);
	rtl8225_write_phy_ofdm(dev, 0x0a, 0x08);
	rtl8225_write_phy_ofdm(dev, 0x0b, 0x80);
	rtl8225_write_phy_ofdm(dev, 0x0c, 0x01);
	rtl8225_write_phy_ofdm(dev, 0x0d, 0x43);
	rtl8225_write_phy_ofdm(dev, 0x0e, 0xd3);
	rtl8225_write_phy_ofdm(dev, 0x0f, 0x38);
	rtl8225_write_phy_ofdm(dev, 0x10, 0x84);
	rtl8225_write_phy_ofdm(dev, 0x11, 0x07);
	rtl8225_write_phy_ofdm(dev, 0x12, 0x20);
	rtl8225_write_phy_ofdm(dev, 0x13, 0x20);
	rtl8225_write_phy_ofdm(dev, 0x14, 0x00);
	rtl8225_write_phy_ofdm(dev, 0x15, 0x40);
	rtl8225_write_phy_ofdm(dev, 0x16, 0x00);
	rtl8225_write_phy_ofdm(dev, 0x17, 0x40);
	rtl8225_write_phy_ofdm(dev, 0x18, 0xef);
	rtl8225_write_phy_ofdm(dev, 0x19, 0x19);
	rtl8225_write_phy_ofdm(dev, 0x1a, 0x20);
	rtl8225_write_phy_ofdm(dev, 0x1b, 0x15);
	rtl8225_write_phy_ofdm(dev, 0x1c, 0x04);
	rtl8225_write_phy_ofdm(dev, 0x1d, 0xc5);
	rtl8225_write_phy_ofdm(dev, 0x1e, 0x95);
	rtl8225_write_phy_ofdm(dev, 0x1f, 0x75);
	rtl8225_write_phy_ofdm(dev, 0x20, 0x1f);
	rtl8225_write_phy_ofdm(dev, 0x21, 0x17);
	rtl8225_write_phy_ofdm(dev, 0x22, 0x16);
	rtl8225_write_phy_ofdm(dev, 0x23, 0x80);
	rtl8225_write_phy_ofdm(dev, 0x24, 0x46);
	rtl8225_write_phy_ofdm(dev, 0x25, 0x00);
	rtl8225_write_phy_ofdm(dev, 0x26, 0x90);
	rtl8225_write_phy_ofdm(dev, 0x27, 0x88);

	rtl8225_write_phy_ofdm(dev, 0x0b, rtl8225z2_gain_bg[4 * 3]);
	rtl8225_write_phy_ofdm(dev, 0x1b, rtl8225z2_gain_bg[4 * 3 + 1]);
	rtl8225_write_phy_ofdm(dev, 0x1d, rtl8225z2_gain_bg[4 * 3 + 2]);
	rtl8225_write_phy_ofdm(dev, 0x21, 0x37);

	rtl8225_write_phy_cck(dev, 0x00, 0x98);
	rtl8225_write_phy_cck(dev, 0x03, 0x20);
	rtl8225_write_phy_cck(dev, 0x04, 0x7e);
	rtl8225_write_phy_cck(dev, 0x05, 0x12);
	rtl8225_write_phy_cck(dev, 0x06, 0xfc);
	rtl8225_write_phy_cck(dev, 0x07, 0x78);
	rtl8225_write_phy_cck(dev, 0x08, 0x2e);
	rtl8225_write_phy_cck(dev, 0x10, 0x9b);
	rtl8225_write_phy_cck(dev, 0x11, 0x88);
	rtl8225_write_phy_cck(dev, 0x12, 0x47);
	rtl8225_write_phy_cck(dev, 0x13, 0xd0);
	rtl8225_write_phy_cck(dev, 0x19, 0x00);
	rtl8225_write_phy_cck(dev, 0x1a, 0xa0);
	rtl8225_write_phy_cck(dev, 0x1b, 0x08);
	rtl8225_write_phy_cck(dev, 0x40, 0x86);
	rtl8225_write_phy_cck(dev, 0x41, 0x8d);
	rtl8225_write_phy_cck(dev, 0x42, 0x15);
	rtl8225_write_phy_cck(dev, 0x43, 0x18);
	rtl8225_write_phy_cck(dev, 0x44, 0x36);
	rtl8225_write_phy_cck(dev, 0x45, 0x35);
	rtl8225_write_phy_cck(dev, 0x46, 0x2e);
	rtl8225_write_phy_cck(dev, 0x47, 0x25);
	rtl8225_write_phy_cck(dev, 0x48, 0x1c);
	rtl8225_write_phy_cck(dev, 0x49, 0x12);
	rtl8225_write_phy_cck(dev, 0x4a, 0x09);
	rtl8225_write_phy_cck(dev, 0x4b, 0x04);
	rtl8225_write_phy_cck(dev, 0x4c, 0x05);

	rtl818x_iowrite8(priv, (u8 *)0xFF5B, 0x0D); msleep(1);

	rtl8225z2_rf_set_tx_power(dev, 1);

	/* RX antenna default to A */
	rtl8225_write_phy_cck(dev, 0x10, 0x9b);			/* B: 0xDB */
	rtl8225_write_phy_ofdm(dev, 0x26, 0x90);		/* B: 0x10 */

	rtl818x_iowrite8(priv, &priv->map->TX_ANTENNA, 0x03);	/* B: 0x00 */
	msleep(1);
	rtl818x_iowrite32(priv, (__le32 *)0xFF94, 0x3dc00002);
}