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
struct rtl8180_priv {TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct eeprom_93cx6 {scalar_t__ reg_chip_select; scalar_t__ reg_data_clock; scalar_t__ reg_data_out; scalar_t__ reg_data_in; struct ieee80211_hw* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  EEPROM_CMD; } ;

/* Variables and functions */
 int RTL818X_EEPROM_CMD_CK ; 
 int RTL818X_EEPROM_CMD_CS ; 
 int RTL818X_EEPROM_CMD_READ ; 
 int RTL818X_EEPROM_CMD_WRITE ; 
 int /*<<< orphan*/  rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtl8180_eeprom_register_write(struct eeprom_93cx6 *eeprom)
{
	struct ieee80211_hw *dev = eeprom->data;
	struct rtl8180_priv *priv = dev->priv;
	u8 reg = 2 << 6;

	if (eeprom->reg_data_in)
		reg |= RTL818X_EEPROM_CMD_WRITE;
	if (eeprom->reg_data_out)
		reg |= RTL818X_EEPROM_CMD_READ;
	if (eeprom->reg_data_clock)
		reg |= RTL818X_EEPROM_CMD_CK;
	if (eeprom->reg_chip_select)
		reg |= RTL818X_EEPROM_CMD_CS;

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, reg);
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(10);
}