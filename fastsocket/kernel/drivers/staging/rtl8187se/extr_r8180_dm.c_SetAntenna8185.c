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
struct r8180_priv {int rf_chip; int CurrAntennaIndex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTSEL ; 
#define  RF_ZEBRA2 129 
#define  RF_ZEBRA4 128 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_phy_cck (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 

bool
SetAntenna8185(
	struct net_device *dev,
	u8		u1bAntennaIndex
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	bool bAntennaSwitched = false;

//	printk("+SetAntenna8185(): Antenna is switching to: %d \n", u1bAntennaIndex);

	switch(u1bAntennaIndex)
	{
	case 0:
		switch(priv->rf_chip)
		{
		case RF_ZEBRA2:
		case RF_ZEBRA4:
			// Mac register, main antenna
			write_nic_byte(dev, ANTSEL, 0x03);
			//base band
			write_phy_cck(dev,0x11, 0x9b); // Config CCK RX antenna.
			write_phy_ofdm(dev, 0x0d, 0x5c); // Config OFDM RX antenna.


			bAntennaSwitched = true;
			break;

		default:
			printk("SetAntenna8185: unkown RFChipID(%d)\n", priv->rf_chip);
			break;
		}
		break;

	case 1:
		switch(priv->rf_chip)
		{
		case RF_ZEBRA2:
		case RF_ZEBRA4:
			// Mac register, aux antenna
			write_nic_byte(dev, ANTSEL, 0x00);
			//base band
			write_phy_cck(dev, 0x11, 0xbb); // Config CCK RX antenna.
			write_phy_ofdm(dev, 0x0d, 0x54); // Config OFDM RX antenna.

			bAntennaSwitched = true;
			break;

		default:
			printk("SetAntenna8185: unkown RFChipID(%d)\n", priv->rf_chip);
			break;
		}
		break;

	default:
		printk("SetAntenna8185: unkown u1bAntennaIndex(%d)\n", u1bAntennaIndex);
		break;
	}

	if(bAntennaSwitched)
	{
		priv->CurrAntennaIndex = u1bAntennaIndex;
	}

//	printk("-SetAntenna8185(): return (%#X)\n", bAntennaSwitched);

	return bAntennaSwitched;
}