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
struct rtl8180_priv {TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct ieee80211_bss_conf {scalar_t__ use_short_slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  CW_VAL; int /*<<< orphan*/  EIFS; int /*<<< orphan*/  DIFS; int /*<<< orphan*/  SIFS; int /*<<< orphan*/  SLOT; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rtl8225_rf_conf_erp(struct ieee80211_hw *dev,
				struct ieee80211_bss_conf *info)
{
	struct rtl8180_priv *priv = dev->priv;

	if (info->use_short_slot) {
		rtl818x_iowrite8(priv, &priv->map->SLOT, 0x9);
		rtl818x_iowrite8(priv, &priv->map->SIFS, 0x22);
		rtl818x_iowrite8(priv, &priv->map->DIFS, 0x14);
		rtl818x_iowrite8(priv, &priv->map->EIFS, 81);
		rtl818x_iowrite8(priv, &priv->map->CW_VAL, 0x73);
	} else {
		rtl818x_iowrite8(priv, &priv->map->SLOT, 0x14);
		rtl818x_iowrite8(priv, &priv->map->SIFS, 0x44);
		rtl818x_iowrite8(priv, &priv->map->DIFS, 0x24);
		rtl818x_iowrite8(priv, &priv->map->EIFS, 81);
		rtl818x_iowrite8(priv, &priv->map->CW_VAL, 0xa5);
	}
}