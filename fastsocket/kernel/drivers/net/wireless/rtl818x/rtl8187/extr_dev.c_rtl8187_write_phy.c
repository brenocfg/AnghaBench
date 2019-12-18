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
typedef  int u32 ;
struct rtl8187_priv {TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * PHY; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 

void rtl8187_write_phy(struct ieee80211_hw *dev, u8 addr, u32 data)
{
	struct rtl8187_priv *priv = dev->priv;

	data <<= 8;
	data |= addr | 0x80;

	rtl818x_iowrite8(priv, &priv->map->PHY[3], (data >> 24) & 0xFF);
	rtl818x_iowrite8(priv, &priv->map->PHY[2], (data >> 16) & 0xFF);
	rtl818x_iowrite8(priv, &priv->map->PHY[1], (data >> 8) & 0xFF);
	rtl818x_iowrite8(priv, &priv->map->PHY[0], data & 0xFF);
}