#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct rtl8180_priv {TYPE_3__* map; scalar_t__ r8185; TYPE_1__* rf; TYPE_2__* tx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  anaparam; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rtl8180_priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  BRSR; int /*<<< orphan*/  CARRIER_SENSE_COUNTER; int /*<<< orphan*/  PHY_DELAY; int /*<<< orphan*/  SECURITY; int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CONFIG3; int /*<<< orphan*/  GP_ENABLE; int /*<<< orphan*/  RESP_RATE; int /*<<< orphan*/  RATE_FALLBACK; int /*<<< orphan*/  WPA_CONF; int /*<<< orphan*/  INT_TIMEOUT; int /*<<< orphan*/  CONFIG2; int /*<<< orphan*/  TLPDA; int /*<<< orphan*/  TNPDA; int /*<<< orphan*/  THPDA; int /*<<< orphan*/  TBDA; int /*<<< orphan*/  RDSAR; int /*<<< orphan*/  MSR; int /*<<< orphan*/  FEMR; int /*<<< orphan*/  CMD; int /*<<< orphan*/  INT_MASK; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RTL818X_CMD_RESET ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_LOAD ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtl8180_set_anaparam (struct rtl8180_priv*,int /*<<< orphan*/ ) ; 
 int rtl818x_ioread16 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtl8180_init_hw(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	u16 reg;

	rtl818x_iowrite8(priv, &priv->map->CMD, 0);
	rtl818x_ioread8(priv, &priv->map->CMD);
	msleep(10);

	/* reset */
	rtl818x_iowrite16(priv, &priv->map->INT_MASK, 0);
	rtl818x_ioread8(priv, &priv->map->CMD);

	reg = rtl818x_ioread8(priv, &priv->map->CMD);
	reg &= (1 << 1);
	reg |= RTL818X_CMD_RESET;
	rtl818x_iowrite8(priv, &priv->map->CMD, RTL818X_CMD_RESET);
	rtl818x_ioread8(priv, &priv->map->CMD);
	msleep(200);

	/* check success of reset */
	if (rtl818x_ioread8(priv, &priv->map->CMD) & RTL818X_CMD_RESET) {
		wiphy_err(dev->wiphy, "reset timeout!\n");
		return -ETIMEDOUT;
	}

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_LOAD);
	rtl818x_ioread8(priv, &priv->map->CMD);
	msleep(200);

	if (rtl818x_ioread8(priv, &priv->map->CONFIG3) & (1 << 3)) {
		/* For cardbus */
		reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
		reg |= 1 << 1;
		rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg);
		reg = rtl818x_ioread16(priv, &priv->map->FEMR);
		reg |= (1 << 15) | (1 << 14) | (1 << 4);
		rtl818x_iowrite16(priv, &priv->map->FEMR, reg);
	}

	rtl818x_iowrite8(priv, &priv->map->MSR, 0);

	if (!priv->r8185)
		rtl8180_set_anaparam(priv, priv->anaparam);

	rtl818x_iowrite32(priv, &priv->map->RDSAR, priv->rx_ring_dma);
	rtl818x_iowrite32(priv, &priv->map->TBDA, priv->tx_ring[3].dma);
	rtl818x_iowrite32(priv, &priv->map->THPDA, priv->tx_ring[2].dma);
	rtl818x_iowrite32(priv, &priv->map->TNPDA, priv->tx_ring[1].dma);
	rtl818x_iowrite32(priv, &priv->map->TLPDA, priv->tx_ring[0].dma);

	/* TODO: necessary? specs indicate not */
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG2);
	rtl818x_iowrite8(priv, &priv->map->CONFIG2, reg & ~(1 << 3));
	if (priv->r8185) {
		reg = rtl818x_ioread8(priv, &priv->map->CONFIG2);
		rtl818x_iowrite8(priv, &priv->map->CONFIG2, reg | (1 << 4));
	}
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	/* TODO: set CONFIG5 for calibrating AGC on rtl8180 + philips radio? */

	/* TODO: turn off hw wep on rtl8180 */

	rtl818x_iowrite32(priv, &priv->map->INT_TIMEOUT, 0);

	if (priv->r8185) {
		rtl818x_iowrite8(priv, &priv->map->WPA_CONF, 0);
		rtl818x_iowrite8(priv, &priv->map->RATE_FALLBACK, 0x81);
		rtl818x_iowrite8(priv, &priv->map->RESP_RATE, (8 << 4) | 0);

		rtl818x_iowrite16(priv, &priv->map->BRSR, 0x01F3);

		/* TODO: set ClkRun enable? necessary? */
		reg = rtl818x_ioread8(priv, &priv->map->GP_ENABLE);
		rtl818x_iowrite8(priv, &priv->map->GP_ENABLE, reg & ~(1 << 6));
		rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
		reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
		rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg | (1 << 2));
		rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);
	} else {
		rtl818x_iowrite16(priv, &priv->map->BRSR, 0x1);
		rtl818x_iowrite8(priv, &priv->map->SECURITY, 0);

		rtl818x_iowrite8(priv, &priv->map->PHY_DELAY, 0x6);
		rtl818x_iowrite8(priv, &priv->map->CARRIER_SENSE_COUNTER, 0x4C);
	}

	priv->rf->init(dev);
	if (priv->r8185)
		rtl818x_iowrite16(priv, &priv->map->BRSR, 0x01F3);
	return 0;
}