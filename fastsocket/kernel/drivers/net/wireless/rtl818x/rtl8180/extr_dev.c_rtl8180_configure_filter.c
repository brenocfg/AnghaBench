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
typedef  scalar_t__ u64 ;
struct rtl8180_priv {int rx_conf; TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  RX_CONF; } ;

/* Variables and functions */
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_OTHER_BSS ; 
 int RTL818X_RX_CONF_CTRL ; 
 int RTL818X_RX_CONF_FCS ; 
 int RTL818X_RX_CONF_MONITOR ; 
 int RTL818X_RX_CONF_MULTICAST ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rtl8180_configure_filter(struct ieee80211_hw *dev,
				     unsigned int changed_flags,
				     unsigned int *total_flags,
				     u64 multicast)
{
	struct rtl8180_priv *priv = dev->priv;

	if (changed_flags & FIF_FCSFAIL)
		priv->rx_conf ^= RTL818X_RX_CONF_FCS;
	if (changed_flags & FIF_CONTROL)
		priv->rx_conf ^= RTL818X_RX_CONF_CTRL;
	if (changed_flags & FIF_OTHER_BSS)
		priv->rx_conf ^= RTL818X_RX_CONF_MONITOR;
	if (*total_flags & FIF_ALLMULTI || multicast > 0)
		priv->rx_conf |= RTL818X_RX_CONF_MULTICAST;
	else
		priv->rx_conf &= ~RTL818X_RX_CONF_MULTICAST;

	*total_flags = 0;

	if (priv->rx_conf & RTL818X_RX_CONF_FCS)
		*total_flags |= FIF_FCSFAIL;
	if (priv->rx_conf & RTL818X_RX_CONF_CTRL)
		*total_flags |= FIF_CONTROL;
	if (priv->rx_conf & RTL818X_RX_CONF_MONITOR)
		*total_flags |= FIF_OTHER_BSS;
	if (priv->rx_conf & RTL818X_RX_CONF_MULTICAST)
		*total_flags |= FIF_ALLMULTI;

	rtl818x_iowrite32(priv, &priv->map->RX_CONF, priv->rx_conf);
}