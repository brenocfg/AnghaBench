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
typedef  int u8 ;
typedef  int u16 ;
struct rtl8180_priv {TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  RFPinsOutput; int /*<<< orphan*/  RFPinsSelect; int /*<<< orphan*/  RFPinsEnable; int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  RFPinsInput; } ;

/* Variables and functions */
 int rtl818x_ioread16 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u16 rtl8225_read(struct ieee80211_hw *dev, u8 addr)
{
	struct rtl8180_priv *priv = dev->priv;
	u16 reg80, reg82, reg84, out;
	int i;

	reg80 = rtl818x_ioread16(priv, &priv->map->RFPinsOutput);
	reg82 = rtl818x_ioread16(priv, &priv->map->RFPinsEnable);
	reg84 = rtl818x_ioread16(priv, &priv->map->RFPinsSelect) | 0x400;

	reg80 &= ~0xF;

	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, reg82 | 0x000F);
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, reg84 | 0x000F);

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg80 | (1 << 2));
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(4);
	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg80);
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(5);

	for (i = 4; i >= 0; i--) {
		u16 reg = reg80 | ((addr >> i) & 1);

		if (!(i & 1)) {
			rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg);
			rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
			udelay(1);
		}

		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
				  reg | (1 << 1));
		rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
		udelay(2);
		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
				  reg | (1 << 1));
		rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
		udelay(2);

		if (i & 1) {
			rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg);
			rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
			udelay(1);
		}
	}

	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, 0x000E);
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, 0x040E);
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
			  reg80 | (1 << 3) | (1 << 1));
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(2);
	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
			  reg80 | (1 << 3));
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(2);
	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
			  reg80 | (1 << 3));
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(2);

	out = 0;
	for (i = 11; i >= 0; i--) {
		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
				  reg80 | (1 << 3));
		rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
		udelay(1);
		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
				  reg80 | (1 << 3) | (1 << 1));
		rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
		udelay(2);
		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
				  reg80 | (1 << 3) | (1 << 1));
		rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
		udelay(2);
		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
				  reg80 | (1 << 3) | (1 << 1));
		rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
		udelay(2);

		if (rtl818x_ioread16(priv, &priv->map->RFPinsInput) & (1 << 1))
			out |= 1 << i;

		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
				  reg80 | (1 << 3));
		rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
		udelay(2);
	}

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput,
			  reg80 | (1 << 3) | (1 << 2));
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(2);

	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, reg82);
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, reg84);
	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, 0x03A0);

	return out;
}