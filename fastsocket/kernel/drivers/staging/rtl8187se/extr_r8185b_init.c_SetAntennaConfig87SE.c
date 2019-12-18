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
struct r8180_priv {int CurrAntennaIndex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTSEL ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_phy_cck (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 

bool
SetAntennaConfig87SE(
	struct net_device *dev,
	u8			DefaultAnt,		// 0: Main, 1: Aux.
	bool		bAntDiversity 	// 1:Enable, 0: Disable.
)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	bool   bAntennaSwitched = true;

	//printk("SetAntennaConfig87SE(): DefaultAnt(%d), bAntDiversity(%d)\n", DefaultAnt, bAntDiversity);

	// Threshold for antenna diversity.
	write_phy_cck(dev, 0x0c, 0x09); // Reg0c : 09

	if( bAntDiversity )  //  Enable Antenna Diversity.
	{
		if( DefaultAnt == 1 )  // aux antenna
		{
			// Mac register, aux antenna
			write_nic_byte(dev, ANTSEL, 0x00);

			// Config CCK RX antenna.
			write_phy_cck(dev, 0x11, 0xbb); // Reg11 : bb
			write_phy_cck(dev, 0x01, 0xc7); // Reg01 : c7

			// Config OFDM RX antenna.
			write_phy_ofdm(dev, 0x0D, 0x54);   // Reg0d : 54
			write_phy_ofdm(dev, 0x18, 0xb2);  // Reg18 : b2
		}
		else //  use main antenna
		{
			// Mac register, main antenna
			write_nic_byte(dev, ANTSEL, 0x03);
			//base band
			// Config CCK RX antenna.
			write_phy_cck(dev, 0x11, 0x9b); // Reg11 : 9b
			write_phy_cck(dev, 0x01, 0xc7); // Reg01 : c7

			// Config OFDM RX antenna.
			write_phy_ofdm(dev, 0x0d, 0x5c);   // Reg0d : 5c
			write_phy_ofdm(dev, 0x18, 0xb2);  // Reg18 : b2
		}
	}
	else   // Disable Antenna Diversity.
	{
		if( DefaultAnt == 1 ) // aux Antenna
		{
			// Mac register, aux antenna
			write_nic_byte(dev, ANTSEL, 0x00);

			// Config CCK RX antenna.
			write_phy_cck(dev, 0x11, 0xbb); // Reg11 : bb
			write_phy_cck(dev, 0x01, 0x47); // Reg01 : 47

			// Config OFDM RX antenna.
			write_phy_ofdm(dev, 0x0D, 0x54);   // Reg0d : 54
			write_phy_ofdm(dev, 0x18, 0x32);  // Reg18 : 32
		}
		else // main Antenna
		{
			// Mac register, main antenna
			write_nic_byte(dev, ANTSEL, 0x03);

			// Config CCK RX antenna.
			write_phy_cck(dev, 0x11, 0x9b); // Reg11 : 9b
			write_phy_cck(dev, 0x01, 0x47); // Reg01 : 47

			// Config OFDM RX antenna.
			write_phy_ofdm(dev, 0x0D, 0x5c);   // Reg0d : 5c
			write_phy_ofdm(dev, 0x18, 0x32);  // Reg18 : 32
		}
	}
	priv->CurrAntennaIndex = DefaultAnt; // Update default settings.
	return	bAntennaSwitched;
}