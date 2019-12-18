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
typedef  int u16 ;
struct r8180_priv {scalar_t__ card_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BB_HOST_BANG_CLK ; 
 int BB_HOST_BANG_EN ; 
 int /*<<< orphan*/  RFPinsEnable ; 
 int /*<<< orphan*/  RFPinsOutput ; 
 int /*<<< orphan*/  RFPinsSelect ; 
 int SW_CONTROL_GPIO ; 
 scalar_t__ USB ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int read_nic_word (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8185_rf_pins_enable (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void write_rtl8225(struct net_device *dev, u8 adr, u16 data)
{
	int i;
	u16 out, select;
	u8 bit;
	u32 bangdata = (data << 4) | (adr & 0xf);
	struct r8180_priv *priv = ieee80211_priv(dev);

	out = read_nic_word(dev, RFPinsOutput) & 0xfff3;

	write_nic_word(dev, RFPinsEnable,
		(read_nic_word(dev, RFPinsEnable) | 0x7));

	select = read_nic_word(dev, RFPinsSelect);

	write_nic_word(dev, RFPinsSelect, select | 0x7 |
		((priv->card_type == USB) ? 0 : SW_CONTROL_GPIO));

	force_pci_posting(dev);
	udelay(10);

	write_nic_word(dev, RFPinsOutput, out | BB_HOST_BANG_EN);

	force_pci_posting(dev);
	udelay(2);

	write_nic_word(dev, RFPinsOutput, out);

	force_pci_posting(dev);
	udelay(10);

	for (i = 15; i >= 0; i--) {
		bit = (bangdata & (1 << i)) >> i;

		write_nic_word(dev, RFPinsOutput, bit | out);

		write_nic_word(dev, RFPinsOutput, bit | out | BB_HOST_BANG_CLK);
		write_nic_word(dev, RFPinsOutput, bit | out | BB_HOST_BANG_CLK);

		i--;
		bit = (bangdata & (1 << i)) >> i;

		write_nic_word(dev, RFPinsOutput, bit | out | BB_HOST_BANG_CLK);
		write_nic_word(dev, RFPinsOutput, bit | out | BB_HOST_BANG_CLK);

		write_nic_word(dev, RFPinsOutput, bit | out);

	}

	write_nic_word(dev, RFPinsOutput, out | BB_HOST_BANG_EN);

	force_pci_posting(dev);
	udelay(10);

	write_nic_word(dev, RFPinsOutput, out |
		((priv->card_type == USB) ? 4 : BB_HOST_BANG_EN));

	write_nic_word(dev, RFPinsSelect, select |
		((priv->card_type == USB) ? 0 : SW_CONTROL_GPIO));

	if (priv->card_type == USB)
		mdelay(2);
	else
		rtl8185_rf_pins_enable(dev);
}