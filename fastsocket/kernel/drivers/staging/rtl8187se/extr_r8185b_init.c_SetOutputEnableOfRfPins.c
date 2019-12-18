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
struct r8180_priv {int rf_chip; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  RFCHIPID_RTL8225 130 
 int /*<<< orphan*/  RFPinsEnable ; 
#define  RF_ZEBRA2 129 
#define  RF_ZEBRA4 128 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

void
SetOutputEnableOfRfPins(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	switch(priv->rf_chip)
	{
	case RFCHIPID_RTL8225:
	case RF_ZEBRA2:
	case RF_ZEBRA4:
		write_nic_word(dev, RFPinsEnable, 0x1bff);
		//write_nic_word(dev, RFPinsEnable, 0x1fff);
		break;
	}
}