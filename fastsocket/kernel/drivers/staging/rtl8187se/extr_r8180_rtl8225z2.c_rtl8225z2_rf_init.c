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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct r8180_priv {short chan; scalar_t__ card_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRSR ; 
 int CONFIG3 ; 
 int /*<<< orphan*/  DMESGW (char*) ; 
 int /*<<< orphan*/  EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  EPROM_CMD_NORMAL ; 
 int RF_PARA ; 
 int RF_TIMING ; 
 scalar_t__ USB ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  read_nic_word (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_rtl8225 (struct net_device*,int) ; 
 int /*<<< orphan*/  rtl8180_set_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8185_rf_pins_enable (struct net_device*) ; 
 int /*<<< orphan*/  rtl8185_tx_antenna (struct net_device*,int) ; 
 int* rtl8225_agc ; 
 int* rtl8225_chan ; 
 int /*<<< orphan*/  rtl8225_host_pci_init (struct net_device*) ; 
 int /*<<< orphan*/  rtl8225_rf_set_chan (struct net_device*,short) ; 
 int /*<<< orphan*/  rtl8225z2_SetTXPowerLevel (struct net_device*,short) ; 
 int* rtl8225z2_rxgain ; 
 int /*<<< orphan*/  rtl8225z2_set_gain (struct net_device*,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_phy_cck (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_rtl8225 (struct net_device*,int,int) ; 

void rtl8225z2_rf_init(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	int i;
	short channel = 1;
	u16	brsr;
	u32	data,addr;

	priv->chan = channel;

	if (priv->card_type != USB)
		rtl8225_host_pci_init(dev);

	write_nic_dword(dev, RF_TIMING, 0x000a8008);

	brsr = read_nic_word(dev, BRSR);

	write_nic_word(dev, BRSR, 0xffff);

	write_nic_dword(dev, RF_PARA, 0x100044);

	rtl8180_set_mode(dev, EPROM_CMD_CONFIG);
	write_nic_byte(dev, CONFIG3, 0x44);
	rtl8180_set_mode(dev, EPROM_CMD_NORMAL);

	rtl8185_rf_pins_enable(dev);

	write_rtl8225(dev, 0x0, 0x2bf); mdelay(1);
	write_rtl8225(dev, 0x1, 0xee0); mdelay(1);
	write_rtl8225(dev, 0x2, 0x44d); mdelay(1);
	write_rtl8225(dev, 0x3, 0x441); mdelay(1);
	write_rtl8225(dev, 0x4, 0x8c3); mdelay(1);
	write_rtl8225(dev, 0x5, 0xc72); mdelay(1);
	write_rtl8225(dev, 0x6, 0xe6);  mdelay(1);
	write_rtl8225(dev, 0x7, ((priv->card_type == USB)? 0x82a : rtl8225_chan[channel]));  mdelay(1);
	write_rtl8225(dev, 0x8, 0x3f);  mdelay(1);
	write_rtl8225(dev, 0x9, 0x335); mdelay(1);
	write_rtl8225(dev, 0xa, 0x9d4); mdelay(1);
	write_rtl8225(dev, 0xb, 0x7bb); mdelay(1);
	write_rtl8225(dev, 0xc, 0x850); mdelay(1);
	write_rtl8225(dev, 0xd, 0xcdf); mdelay(1);
	write_rtl8225(dev, 0xe, 0x2b);  mdelay(1);
	write_rtl8225(dev, 0xf, 0x114);

	mdelay(100);

	write_rtl8225(dev, 0x0, 0x1b7);

	for (i = 0; i < 95; i++) {
		write_rtl8225(dev, 0x1, (u8)(i + 1));
		write_rtl8225(dev, 0x2, rtl8225z2_rxgain[i]);
	}

	write_rtl8225(dev, 0x3, 0x80);
	write_rtl8225(dev, 0x5, 0x4);

	write_rtl8225(dev, 0x0, 0xb7);

	write_rtl8225(dev, 0x2, 0xc4d);

	if (priv->card_type == USB) {
		mdelay(200);

		write_rtl8225(dev, 0x2, 0x44d);
		mdelay(100);
	}

	/* FIXME!! rtl8187 we have to check if calibrarion
	 * is successful and eventually cal. again (repeat
	 * the two write on reg 2)
	 */
	data = read_rtl8225(dev, 6);
	if (!(data & 0x00000080)) {
		write_rtl8225(dev, 0x02, 0x0c4d);
		force_pci_posting(dev); mdelay(200);
		write_rtl8225(dev, 0x02, 0x044d);
		force_pci_posting(dev); mdelay(100);
		data = read_rtl8225(dev, 6);
		if (!(data & 0x00000080))
			DMESGW("RF Calibration Failed!!!!\n");
	}

	mdelay(200);

	write_rtl8225(dev, 0x0, 0x2bf);

	if (priv->card_type != USB)
		rtl8185_rf_pins_enable(dev);

	for (i = 0; i < 128; i++) {
		data = rtl8225_agc[i];

		addr = i + 0x80; /* enable writing AGC table */
		write_phy_ofdm(dev, 0xb, data);
		mdelay(1);

		write_phy_ofdm(dev, 0xa, addr);
		mdelay(1);
	}

	force_pci_posting(dev);
	mdelay(1);

	write_phy_ofdm(dev, 0x00, 0x01); mdelay(1);
	write_phy_ofdm(dev, 0x01, 0x02); mdelay(1);
	write_phy_ofdm(dev, 0x02, ((priv->card_type == USB) ? 0x42 : 0x62)); mdelay(1);
	write_phy_ofdm(dev, 0x03, 0x00); mdelay(1);
	write_phy_ofdm(dev, 0x04, 0x00); mdelay(1);
	write_phy_ofdm(dev, 0x05, 0x00); mdelay(1);
	write_phy_ofdm(dev, 0x06, 0x40); mdelay(1);
	write_phy_ofdm(dev, 0x07, 0x00); mdelay(1);
	write_phy_ofdm(dev, 0x08, 0x40); mdelay(1);
	write_phy_ofdm(dev, 0x09, 0xfe); mdelay(1);
	write_phy_ofdm(dev, 0x0a, 0x08); mdelay(1);
	write_phy_ofdm(dev, 0x0b, 0x80); mdelay(1);
	write_phy_ofdm(dev, 0x0c, 0x01); mdelay(1);
	write_phy_ofdm(dev, 0x0d, 0x43);
	write_phy_ofdm(dev, 0x0e, 0xd3); mdelay(1);
	write_phy_ofdm(dev, 0x0f, 0x38); mdelay(1);
	write_phy_ofdm(dev, 0x10, 0x84); mdelay(1);
	write_phy_ofdm(dev, 0x11, 0x07); mdelay(1);
	write_phy_ofdm(dev, 0x12, 0x20); mdelay(1);
	write_phy_ofdm(dev, 0x13, 0x20); mdelay(1);
	write_phy_ofdm(dev, 0x14, 0x00); mdelay(1);
	write_phy_ofdm(dev, 0x15, 0x40); mdelay(1);
	write_phy_ofdm(dev, 0x16, 0x00); mdelay(1);
	write_phy_ofdm(dev, 0x17, 0x40); mdelay(1);
	write_phy_ofdm(dev, 0x18, 0xef); mdelay(1);
	write_phy_ofdm(dev, 0x19, 0x19); mdelay(1);
	write_phy_ofdm(dev, 0x1a, 0x20); mdelay(1);
	write_phy_ofdm(dev, 0x1b, 0x15); mdelay(1);
	write_phy_ofdm(dev, 0x1c, 0x04); mdelay(1);
	write_phy_ofdm(dev, 0x1d, 0xc5); mdelay(1);
	write_phy_ofdm(dev, 0x1e, 0x95); mdelay(1);
	write_phy_ofdm(dev, 0x1f, 0x75); mdelay(1);
	write_phy_ofdm(dev, 0x20, 0x1f); mdelay(1);
	write_phy_ofdm(dev, 0x21, 0x17); mdelay(1);
	write_phy_ofdm(dev, 0x22, 0x16); mdelay(1);
	write_phy_ofdm(dev, 0x23, 0x80); mdelay(1); /* FIXME maybe not needed */
	write_phy_ofdm(dev, 0x24, 0x46); mdelay(1);
	write_phy_ofdm(dev, 0x25, 0x00); mdelay(1);
	write_phy_ofdm(dev, 0x26, 0x90); mdelay(1);
	write_phy_ofdm(dev, 0x27, 0x88); mdelay(1);

	rtl8225z2_set_gain(dev,4);

	write_phy_cck(dev, 0x0, 0x98); mdelay(1);
	write_phy_cck(dev, 0x3, 0x20); mdelay(1);
	write_phy_cck(dev, 0x4, 0x7e); mdelay(1);
	write_phy_cck(dev, 0x5, 0x12); mdelay(1);
	write_phy_cck(dev, 0x6, 0xfc); mdelay(1);
	write_phy_cck(dev, 0x7, 0x78); mdelay(1);
	write_phy_cck(dev, 0x8, 0x2e); mdelay(1);
	write_phy_cck(dev, 0x10, ((priv->card_type == USB) ? 0x9b: 0x93)); mdelay(1);
	write_phy_cck(dev, 0x11, 0x88); mdelay(1);
	write_phy_cck(dev, 0x12, 0x47); mdelay(1);
	write_phy_cck(dev, 0x13, 0xd0);
	write_phy_cck(dev, 0x19, 0x00);
	write_phy_cck(dev, 0x1a, 0xa0);
	write_phy_cck(dev, 0x1b, 0x08);
	write_phy_cck(dev, 0x40, 0x86); /* CCK Carrier Sense Threshold */
	write_phy_cck(dev, 0x41, 0x8d); mdelay(1);
	write_phy_cck(dev, 0x42, 0x15); mdelay(1);
	write_phy_cck(dev, 0x43, 0x18); mdelay(1);
	write_phy_cck(dev, 0x44, 0x36); mdelay(1);
	write_phy_cck(dev, 0x45, 0x35); mdelay(1);
	write_phy_cck(dev, 0x46, 0x2e); mdelay(1);
	write_phy_cck(dev, 0x47, 0x25); mdelay(1);
	write_phy_cck(dev, 0x48, 0x1c); mdelay(1);
	write_phy_cck(dev, 0x49, 0x12); mdelay(1);
	write_phy_cck(dev, 0x4a, 0x09); mdelay(1);
	write_phy_cck(dev, 0x4b, 0x04); mdelay(1);
	write_phy_cck(dev, 0x4c, 0x05); mdelay(1);

	write_nic_byte(dev, 0x5b, 0x0d); mdelay(1);

	rtl8225z2_SetTXPowerLevel(dev, channel);

	/* RX antenna default to A */
	write_phy_cck(dev, 0x11, 0x9b); mdelay(1);		/* B: 0xDB */
	write_phy_ofdm(dev, 0x26, 0x90); mdelay(1);		/* B: 0x10 */

	rtl8185_tx_antenna(dev, 0x03);				/* B: 0x00 */

	/* switch to high-speed 3-wire
	 * last digit. 2 for both cck and ofdm
	 */
	if (priv->card_type == USB)
		write_nic_dword(dev, 0x94, 0x3dc00002);
	else {
		write_nic_dword(dev, 0x94, 0x15c00002);
		rtl8185_rf_pins_enable(dev);
	}

	rtl8225_rf_set_chan(dev, priv->chan);
}