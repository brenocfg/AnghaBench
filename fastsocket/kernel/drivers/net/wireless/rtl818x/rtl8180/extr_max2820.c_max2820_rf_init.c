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
struct TYPE_2__ {int /*<<< orphan*/  CONFIG2; } ;

/* Variables and functions */
 int RTL818X_CONFIG2_ANTENNA_DIV ; 
 int /*<<< orphan*/  max2820_rf_set_channel (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max2820_write_phy_antenna (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8180_write_phy (struct ieee80211_hw*,int,int) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_max2820 (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void max2820_rf_init(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;

	/* MAXIM from netbsd driver */
	write_max2820(dev, 0, 0x007); /* test mode as indicated in datasheet */
	write_max2820(dev, 1, 0x01e); /* enable register */
	write_max2820(dev, 2, 0x001); /* synt register */

	max2820_rf_set_channel(dev, NULL);

	write_max2820(dev, 4, 0x313); /* rx register */

	/* PA is driven directly by the BB, we keep the MAXIM bias
	 * at the highest value in case that setting it to lower
	 * values may introduce some further attenuation somewhere..
	 */
	write_max2820(dev, 5, 0x00f);

	/* baseband configuration */
	rtl8180_write_phy(dev, 0, 0x88); /* sys1       */
	rtl8180_write_phy(dev, 3, 0x08); /* txagc      */
	rtl8180_write_phy(dev, 4, 0xf8); /* lnadet     */
	rtl8180_write_phy(dev, 5, 0x90); /* ifagcinit  */
	rtl8180_write_phy(dev, 6, 0x1a); /* ifagclimit */
	rtl8180_write_phy(dev, 7, 0x64); /* ifagcdet   */

	max2820_write_phy_antenna(dev, 1);

	rtl8180_write_phy(dev, 0x11, 0x88); /* trl */

	if (rtl818x_ioread8(priv, &priv->map->CONFIG2) &
	    RTL818X_CONFIG2_ANTENNA_DIV)
		rtl8180_write_phy(dev, 0x12, 0xc7);
	else
		rtl8180_write_phy(dev, 0x12, 0x47);

	rtl8180_write_phy(dev, 0x13, 0x9b);

	rtl8180_write_phy(dev, 0x19, 0x0);  /* CHESTLIM */
	rtl8180_write_phy(dev, 0x1a, 0x9f); /* CHSQLIM  */

	max2820_rf_set_channel(dev, NULL);
}