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
struct rtl8180_priv {int csthreshold; TYPE_1__* map; int /*<<< orphan*/  anaparam; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  CONFIG2; } ;

/* Variables and functions */
 int RTL818X_CONFIG2_ANTENNA_DIV ; 
 int /*<<< orphan*/  grf5101_write_phy_antenna (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8180_set_anaparam (struct rtl8180_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_write_phy (struct ieee80211_hw*,int,int) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_grf5101 (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void grf5101_rf_init(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;

	rtl8180_set_anaparam(priv, priv->anaparam);

	write_grf5101(dev, 0x1f, 0x0);
	write_grf5101(dev, 0x1f, 0x0);
	write_grf5101(dev, 0x1f, 0x40);
	write_grf5101(dev, 0x1f, 0x60);
	write_grf5101(dev, 0x1f, 0x61);
	write_grf5101(dev, 0x1f, 0x61);
	write_grf5101(dev, 0x00, 0xae4);
	write_grf5101(dev, 0x1f, 0x1);
	write_grf5101(dev, 0x1f, 0x41);
	write_grf5101(dev, 0x1f, 0x61);

	write_grf5101(dev, 0x01, 0x1a23);
	write_grf5101(dev, 0x02, 0x4971);
	write_grf5101(dev, 0x03, 0x41de);
	write_grf5101(dev, 0x04, 0x2d80);
	write_grf5101(dev, 0x05, 0x68ff);	/* 0x61ff original value */
	write_grf5101(dev, 0x06, 0x0);
	write_grf5101(dev, 0x07, 0x0);
	write_grf5101(dev, 0x08, 0x7533);
	write_grf5101(dev, 0x09, 0xc401);
	write_grf5101(dev, 0x0a, 0x0);
	write_grf5101(dev, 0x0c, 0x1c7);
	write_grf5101(dev, 0x0d, 0x29d3);
	write_grf5101(dev, 0x0e, 0x2e8);
	write_grf5101(dev, 0x10, 0x192);
	write_grf5101(dev, 0x11, 0x248);
	write_grf5101(dev, 0x12, 0x0);
	write_grf5101(dev, 0x13, 0x20c4);
	write_grf5101(dev, 0x14, 0xf4fc);
	write_grf5101(dev, 0x15, 0x0);
	write_grf5101(dev, 0x16, 0x1500);

	write_grf5101(dev, 0x07, 0x1000);

	/* baseband configuration */
	rtl8180_write_phy(dev, 0, 0xa8);
	rtl8180_write_phy(dev, 3, 0x0);
	rtl8180_write_phy(dev, 4, 0xc0);
	rtl8180_write_phy(dev, 5, 0x90);
	rtl8180_write_phy(dev, 6, 0x1e);
	rtl8180_write_phy(dev, 7, 0x64);

	grf5101_write_phy_antenna(dev, 1);

	rtl8180_write_phy(dev, 0x11, 0x88);

	if (rtl818x_ioread8(priv, &priv->map->CONFIG2) &
	    RTL818X_CONFIG2_ANTENNA_DIV)
		rtl8180_write_phy(dev, 0x12, 0xc0); /* enable ant diversity */
	else
		rtl8180_write_phy(dev, 0x12, 0x40); /* disable ant diversity */

	rtl8180_write_phy(dev, 0x13, 0x90 | priv->csthreshold);

	rtl8180_write_phy(dev, 0x19, 0x0);
	rtl8180_write_phy(dev, 0x1a, 0xa0);
	rtl8180_write_phy(dev, 0x1b, 0x44);
}